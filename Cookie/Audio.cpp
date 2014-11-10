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

SDL_semaphore* audio_queue_semaphore;
SDL_Thread* audio_queue_thread = NULL;

int Cookie::audio_queue_thread_func (void * udata);

void Cookie::audio_pipeline_callback(const Uint8* const data, Uint32 len, void* userdata);

#pragma mark - Ctr & Dstrc

Cookie::Audio::Audio()
{
}

Cookie::Audio::~Audio()
{
    SDL_CloseAudioDevice(device_);
    SDL_DetachThread(audio_queue_thread);
    
    delete audio_pipeline_;
    
    SDL_DestroySemaphore(audio_queue_semaphore);
}

void Cookie::Audio::init()
{
    SDL_AudioSpec want;
    
    SDL_zero(want);
    want.freq = 48000;
    want.format = AUDIO_F32;
    want.channels = 2;
    want.samples = 4096;
    want.userdata = this;
    
    device_ = SDL_OpenAudioDevice(NULL, 0, &want, &device_audio_spec_, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device_ == 0) {
        printf("Failed to open audio: %s\n", SDL_GetError());
    } else {
        if (device_audio_spec_.format != want.format)
            printf("We didn't get Float32 audio format.\n");
        
        audio_pipeline_ = new Cookie::AudioPipeline(device_audio_spec_, audio_pipeline_callback);
        audio_pipeline_->userdata = this;
        
        SDL_PauseAudioDevice(device_, 0);

        audio_queue_semaphore = SDL_CreateSemaphore(1);
        audio_queue_thread = SDL_CreateThread(Cookie::audio_queue_thread_func, "CookieAudioQueueThread", this);
        
//        test_sound = new Cookie::Sound(this);
//        test_sound->open(std::string("death01.wav"));
//        test_sound->volume_ = 0.5f;
//        test_sound->play(3);
//        
//        test_sound2 = new Cookie::Sound(this);
//        test_sound2->open(std::string("song.wav"));
//        test_sound2->volume_ = 0.5f;
//        test_sound2->play(10);
    }
}

SDL_AudioSpec Cookie::Audio::get_audio_spec() const
{
    return device_audio_spec_;
}

#pragma mark - Audio Queueing

void Cookie::Audio::queue(Cookie::Sound* sound)
{
    SDL_assert(sound->is_playing() && sound->loop_ > 0);
    SDL_SemWait(audio_queue_semaphore);
    auto found = std::find(sound_queue_.begin(), sound_queue_.end(), sound);
    if(found == sound_queue_.end())
    {
        sound_queue_.push_back(sound);
    }
    SDL_SemPost(audio_queue_semaphore);
}

int Cookie::audio_queue_thread_func (void * udata)
{
    auto audio = static_cast<Cookie::Audio*>(udata);
    std::vector<Cookie::Sound*> sounds_to_remove;
    while (audio != NULL) {
        Cookie::Sound* sound = NULL;
        SDL_SemWait(audio_queue_semaphore);
        if(!audio->sound_queue_.empty())
        {
            for(auto it = audio->sound_queue_.begin(); it != audio->sound_queue_.end(); ++it)
            {
                sound = dynamic_cast<Cookie::Sound*>(*it);
                SDL_LockMutex(sound->sound_mutex_);
                if(sound != NULL && sound->is_playing())
                {
                    Uint32 len = std::min(sound->buffer_length_-sound->buffer_pos_,
                                          (Uint32)audio->device_audio_spec_.samples);
                    Cookie::Int channel = sound->channel_ > 0 ?
                    sound->channel_ :
                    audio->audio_pipeline_->get_next_channel();
                    
                    audio->audio_pipeline_->set_volume(sound->volume_, channel);
                    audio->audio_pipeline_->push(sound->buffer_+sound->buffer_pos_, len, channel);
                    sound->buffer_pos_ += len;
                    if(sound->buffer_pos_ >= sound->buffer_length_)
                    {
                        sound->buffer_pos_ = 0;
                        sound->loop_--;
                        if(sound->loop_ <= 0)
                        {
                            SDL_UnlockMutex(sound->sound_mutex_);
                            sound->stop();
                            SDL_LockMutex(sound->sound_mutex_);
                            sounds_to_remove.push_back(sound);
                        }
                    }
                }
                SDL_UnlockMutex(sound->sound_mutex_);
            }
            audio->audio_pipeline_->flush();
            for(auto it = sounds_to_remove.begin(); it != sounds_to_remove.end(); ++it)
            {
                audio->sound_queue_.erase(std::find(audio->sound_queue_.begin(), audio->sound_queue_.end(), *it));
            }
            sounds_to_remove.clear();
        }
        SDL_SemPost(audio_queue_semaphore);
        
        Uint32 wait = audio->device_audio_spec_.samples /
        (double)audio->device_audio_spec_.freq * 100; //No idea why 100 works
        SDL_Delay(wait);
    }
    return 0;
}

#pragma mark - Audio Pipeline Callback

void Cookie::audio_pipeline_callback(const Uint8* const data, Uint32 len, void* userdata)
{
    static Cookie::Audio* audio = static_cast<Cookie::Audio*>(userdata);
    
//    printf("Pipeline callback len=%d \n", len);
    SDL_assert(len != 0);
    
//    for(int i = 0; i < 16; ++i) { printf("%d,",data[i]); } printf("\n");
    
    SDL_QueueAudio(audio->device_, data, len);
}
