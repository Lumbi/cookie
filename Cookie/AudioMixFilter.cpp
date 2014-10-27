//
//  AudioMixFilter.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioMixFilter.h"
#include <SDL2/SDL.h>
#include <cmath>

Cookie::AudioMixFilter::AudioMixFilter(SDL_AudioSpec audio_spec) : Cookie::AudioFilter(audio_spec)
{
    acc_buffer_ = NULL;
}


Cookie::AudioMixFilter::~AudioMixFilter()
{
    delete acc_buffer_;
}

void Cookie::AudioMixFilter::process(const Uint8* const buf, Uint32 len)
{
    if(len != 0)
    {
        if(acc_buffer_ == NULL)
        {
            acc_buffer_ = new Uint8[len];
            SDL_memset(acc_buffer_, 0, len);
            acc_len_ = len;
        }else if(acc_len_ < len){
            Uint8* acc_buffer_temp_ = new Uint8[len];
            SDL_memcpy(acc_buffer_temp_, acc_buffer_, acc_len_);
            SDL_memset(acc_buffer_temp_ + acc_len_, 0, len - acc_len_);
            delete acc_buffer_;
            acc_buffer_ = acc_buffer_temp_;
            acc_len_ = len;
        }
        SDL_MixAudioFormat(acc_buffer_, buf, audio_spec_.format, len, SDL_MIX_MAXVOLUME);
    }
}

void Cookie::AudioMixFilter::flush()
{
    if(acc_len_ != 0)
    {
        out_->process(acc_buffer_, acc_len_);
        delete acc_buffer_;
        acc_buffer_ = NULL;
        acc_len_ = 0;
    }else{
        out_->process(NULL, 0);
    }
    
}