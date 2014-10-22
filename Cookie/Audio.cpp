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

void audio_pipeline_callback(Uint8* data, Uint32 len)
{
    printf("I'm rich %d \n", len);
}

Cookie::AudioPipeline* audio_pipeline_ = NULL;

template<typename T>
inline T* memcat(T* combined, T* buff1, int len1, T* buff2, int len2)
{
    memcpy(combined, buff1, len1);
    memcpy(combined + len1, buff2, len2);
    return combined;
}

Uint8* channel1_buffer;
Uint32 channel1_buffer_len;
Uint32 offset = 0;

void audio_callback(void *udata, Uint8 *stream, int len)
{
    static Cookie::Audio* audio = static_cast<Cookie::Audio*>(udata);
    SDL_memset(stream, 0, len);
    
    if(channel1_buffer_len > 0)
    {
        if(len > channel1_buffer_len)
        {
//            SDL_MixAudioFormat(stream, channel1_buffer + offset, AUDIO_F32, channel1_buffer_len, SDL_MIX_MAXVOLUME / 2);
//            SDL_memcpy(stream, channel1_buffer, channel1_buffer_len);
        }else{
            if(offset > channel1_buffer_len + len)
            {
                offset = 0;
            }
            SDL_MixAudioFormat(stream, channel1_buffer + offset, AUDIO_F32, len, SDL_MIX_MAXVOLUME);
            offset += len;
//            SDL_memcpy(stream, channel1_buffer, len);
        }
    }
}

Cookie::Audio::Audio()
{
    channel1_buffer = new Uint8[1024];
    memset(channel1_buffer, 0, 1024);
    channel1_buffer_len = 1024;
}

Cookie::Audio::~Audio()
{
    SDL_CloseAudioDevice(device_);
    delete channel1_buffer;
    delete audio_pipeline_;
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
    want.callback = audio_callback;
    
    device_ = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device_ == 0) {
        printf("Failed to open audio: %s\n", SDL_GetError());
    } else {
        if (have.format != want.format)
            printf("We didn't get Float32 audio format.\n");
        
        audio_pipeline_ = new Cookie::AudioPipeline(have, audio_pipeline_callback);
        
//        SDL_PauseAudioDevice(device_, 0);
        
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
            
            audio_pipeline_->push(cvt.buf, 1024);
            audio_pipeline_->flush();
            
            delete channel1_buffer;
            channel1_buffer = new Uint8[cvt.len * cvt.len_mult];
            SDL_memcpy(channel1_buffer, cvt.buf, cvt.len * cvt.len_mult);
            channel1_buffer_len = cvt.len * cvt.len_mult;
            SDL_FreeWAV(wav_buffer);
        }
    }
}