//
//  AudioFilter.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioFilter.h"

Cookie::AudioFilter::AudioFilter(SDL_AudioSpec audio_spec)
{
    audio_spec_ = audio_spec;
}

Cookie::AudioFilter::~AudioFilter()
{
}

Cookie::AudioFilter* const Cookie::AudioFilter::set_output(Cookie::AudioFilter* out)
{
    out_ = out;
    return out_;
}