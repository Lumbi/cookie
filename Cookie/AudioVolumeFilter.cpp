//
//  AudioVolumeFilter.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioVolumeFilter.h"

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
    printf("AudioVolumeFilter\n");
    Uint8* temp = new Uint8[len];
    for(int i = 0; i < len; ++i)
    {
#warning DANGER! No clamping! Big-endianness? does it matter? so many questions ;)
        temp[i] = volume_ * buf[i];
    }
    out_->process(temp, len);
    delete temp;
}

void Cookie::AudioVolumeFilter::set_volume(Cookie::Float volume)
{
    volume_ = volume;
}