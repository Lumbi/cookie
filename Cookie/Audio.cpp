//
//  Audio.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Audio.h"
#include <SDL2/SDL.h>
#include <cmath>
#include "AudioPipeline.h"
#include "Sound.h"

#pragma mark - Forward Declarations

#warning TESTING
Cookie::Sound* test_sound;

SDL_AudioDeviceID device;

static SDL_semaphore* audio_device_buffer_semaphore = NULL;

Uint8** audio_device_buffers = NULL;
Uint32 audio_device_buffer_len;
Uint8* audio_device_write_buffer = NULL;
Uint8* audio_device_read_buffer = NULL;

static SDL_semaphore* audio_queue_semaphore = NULL;

SDL_Thread* audio_queue_thread = NULL;
int Cookie::audio_queue_thread_func (void * udata);

Cookie::AudioPipeline* audio_pipeline_ = NULL;
void audio_pipeline_callback(const Uint8* const data, Uint32 len);

void audio_callback(void *udata, Uint8 *stream, int len);

#pragma mark - Ctr & Dstrc

Cookie::Audio::Audio()
{
    audio_queue_semaphore = SDL_CreateSemaphore(1);
    audio_device_buffer_semaphore = SDL_CreateSemaphore(1);
    audio_queue_thread = SDL_CreateThread(Cookie::audio_queue_thread_func, "CookieAudioQueueThread", this);
}

Cookie::Audio::~Audio()
{
    SDL_CloseAudioDevice(device);
    SDL_DetachThread(audio_queue_thread);
    
    for(int i = 0; i < audio_device_buffer_len; ++i)
    {
        delete audio_device_buffers[i];
    }
    delete audio_pipeline_;
    SDL_DestroySemaphore(audio_queue_semaphore);
    SDL_DestroySemaphore(audio_device_buffer_semaphore);
}

void Cookie::Audio::init()
{
    SDL_AudioSpec want, have;
    
    SDL_zero(want);
    want.freq = 48000;
    want.format = AUDIO_F32;
    want.channels = 2;
    want.samples = 4096;
    want.userdata = this;
    
    device = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device == 0) {
        printf("Failed to open audio: %s\n", SDL_GetError());
    } else {
        if (have.format != want.format)
            printf("We didn't get Float32 audio format.\n");
        
        audio_pipeline_ = new Cookie::AudioPipeline(have, audio_pipeline_callback);
        
        SDL_PauseAudioDevice(device, 0);
        
        SDL_AudioSpec wav_spec;
        Uint32 wav_length;
        Uint8 *wav_buffer;
        
        if (SDL_LoadWAV("death01.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
            fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
        } else {
            
            SDL_AudioCVT cvt;
            SDL_BuildAudioCVT(&cvt, wav_spec.format, wav_spec.channels, wav_spec.freq,
                              have.format, have.channels, have.freq);
            cvt.len = wav_length;
            cvt.buf = (Uint8 *) SDL_malloc(cvt.len * cvt.len_mult);
            SDL_memcpy(cvt.buf, wav_buffer, wav_length);
            SDL_ConvertAudio(&cvt);
            
            test_sound = new Cookie::Sound(this);
            test_sound->buffer_ = cvt.buf;
            test_sound->buffer_length_ = cvt.len * cvt.len_mult;
            test_sound->buffer_pos_ = 0;
            
            test_sound->is_playing_ = true;
            test_sound->loop_ = 5;
            
            queue(test_sound);
            
            //            for(int i = 0; i < 16; ++i) { printf("%d,",cvt.buf[i]); } printf("\n");
            //            audio_pipeline_->set_volume(0.5f);
            
            //            delete channel1_buffer;
            //            channel1_buffer = new Uint8[cvt.len * cvt.len_mult];
            //            SDL_memcpy(channel1_buffer, cvt.buf, cvt.len * cvt.len_mult);
            //            channel1_buffer_len = cvt.len * cvt.len_mult;
            SDL_FreeWAV(wav_buffer);
        }
    }
}

#pragma mark - Audio Queueing

void Cookie::Audio::queue(Cookie::Sound* sound)
{
    SDL_assert(sound->is_playing() && sound->loop_ > 0);
//    printf("1 sem wait...\n");
    SDL_SemWait(audio_queue_semaphore);
//    printf("1 sem get!\n");
    auto found = std::find(sound_queue_.begin(), sound_queue_.end(), sound);
    if(found == sound_queue_.end())
    {
        sound_queue_.push_back(sound);
    }
    SDL_SemPost(audio_queue_semaphore);
//    printf("1 sem released!\n");
}

int Cookie::audio_queue_thread_func (void * udata)
{
    auto audio = static_cast<Cookie::Audio*>(udata);
    std::vector<Cookie::Sound*> sounds_to_remove;
    while (1) {
        Cookie::Sound* sound = NULL;
//        printf("2 sem wait...\n");
        SDL_SemWait(audio_queue_semaphore);
//        printf("2 sem get!\n");
        if(!audio->sound_queue_.empty())
        {
            for(auto it = audio->sound_queue_.begin(); it != audio->sound_queue_.end(); ++it)
            {
                sound = dynamic_cast<Cookie::Sound*>(*it);
                if(sound != NULL && sound->is_playing())
                {
                    Uint32 len = std::min(sound->buffer_length_-sound->buffer_pos_, kAudioBufferLength);
                    audio_pipeline_->push(sound->buffer_+sound->buffer_pos_, len);
                    sound->buffer_pos_ += len;
                    if(sound->buffer_pos_ >= sound->buffer_length_)
                    {
                        sound->buffer_pos_ = 0;
                        sound->loop_--;
                        if(sound->loop_ <= 0)
                        {
                            sound->stop();
                            sounds_to_remove.push_back(sound);
                        }
                    }
                }
            }
            for(auto it = sounds_to_remove.begin(); it != sounds_to_remove.end(); ++it)
            {
#error UNSAFE, THREADING PROBLEM *it IS NULL
                if(*it != NULL)
                {
                    audio->sound_queue_.erase(it);
                }
            }
            sounds_to_remove.clear();
        }
        SDL_SemPost(audio_queue_semaphore);
//        printf("2 sem released!\n");
    }
}

#pragma mark - Audio Pipeline Callback

void audio_pipeline_callback(const Uint8* const data, Uint32 len)
{
    printf("Pipeline callback len=%d \n", len);
    SDL_assert(len != 0);
    
    for(int i = 0; i < 16; ++i) { printf("%d,",data[i]); } printf("\n");
    
//    static const Uint32 MAX_QUEUE_LEN = UINT32_MAX / 2;
//    while(SDL_GetQueuedAudioSize(device) > MAX_QUEUE_LEN)
//    {
//        SDL_Delay(10);
//    }
    SDL_QueueAudio(device, data, len);
    audio_pipeline_->flush();
}

#pragma mark - Audio Device Callback

template<typename T>
inline T* memcat(T* combined, T* buff1, int len1, T* buff2, int len2)
{
    memcpy(combined, buff1, len1);
    memcpy(combined + len1, buff2, len2);
    return combined;
}

//void audio_callback(void *udata, Uint8 *stream, int len)
//{
//    static Cookie::Audio* audio = static_cast<Cookie::Audio*>(udata);
//    SDL_memset(stream, 0, len);
//    
//    if(channel1_buffer_len > 0)
//    {
//        if(len > channel1_buffer_len)
//        {
////            SDL_MixAudioFormat(stream, channel1_buffer + offset, AUDIO_F32, channel1_buffer_len, SDL_MIX_MAXVOLUME / 2);
////            SDL_memcpy(stream, channel1_buffer, channel1_buffer_len);
//        }else{
//            if(offset > channel1_buffer_len + len)
//            {
//                offset = 0;
//            }
//            SDL_memcpy(stream, channel1_buffer + offset, len);
////            SDL_MixAudioFormat(stream, channel1_buffer + offset, AUDIO_F32, len, SDL_MIX_MAXVOLUME);
//            offset += len;
////            SDL_memcpy(stream, channel1_buffer, len);
//        }
//    }
//    
//    
//}




