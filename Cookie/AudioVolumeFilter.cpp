//
//  AudioVolumeFilter.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioVolumeFilter.h"
#include <SDL2/SDL.h>

Cookie::AudioVolumeFilter::AudioVolumeFilter(SDL_AudioSpec audio_spec,
                                             Cookie::Float volume) : Cookie::AudioFilter(audio_spec)
{
    volume_ = volume;
}

Cookie::AudioVolumeFilter::~AudioVolumeFilter()
{
}

void Cookie::AudioVolumeFilter::process(const Uint8* const buf, Uint32 len)
{
#warning this relies on the fact that len doesn't change
    if(len != 0)
    {
        static Uint8* temp = new Uint8[len];
        SDL_memset(temp, 0, len);
        SDL_MixAudioFormat(temp, buf, audio_spec_.format, len, (int)(SDL_MIX_MAXVOLUME * volume_));
        out_->process(temp, len);
    }else{
        out_->process(NULL, len);
    }
}

void Cookie::AudioVolumeFilter::set_volume(Cookie::Float volume)
{
    volume_ = volume;
}