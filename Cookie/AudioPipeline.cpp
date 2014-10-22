//
//  AudioPipeline.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioPipeline.h"

Cookie::AudioPipeline::AudioPipeline(SDL_AudioSpec audio_spec,
                                     Cookie::AudioPipelineCallback callback) : Cookie::AudioFilter(audio_spec)
{
    callback_ = callback;
    
    channel1_ = new Cookie::AudioVolumeFilter(audio_spec);
    mixer_ = new Cookie::AudioMixFilter(audio_spec);
    
    channel1_->set_output(mixer_);
    
    mixer_->set_output(this);
}

Cookie::AudioPipeline::~AudioPipeline()
{
    delete channel1_;
    delete mixer_;
}

void Cookie::AudioPipeline::push(Uint8* data, Uint32 len, Cookie::Int channel)
{
    static Cookie::Int last_channel = 0;
    static const Cookie::Int channel_size = 1;
    
    if(channel == 0)
    {
//        channel = (last_channel+1) % channel_size;
        channel = 1;
    }
    
    switch (channel) {
        case 1:
            channel1_->process(data, len);
            break;
        default:
            break;
    }
    
    last_channel = channel;
}

void Cookie::AudioPipeline::flush()
{
    mixer_->flush();
}

void Cookie::AudioPipeline::process(const Uint8* const data, Uint32 len)
{
    Uint8* cpy = new Uint8[len];
    SDL_memcpy(cpy, data, len);
    callback_(cpy, len);
    delete cpy;
}

void Cookie::AudioPipeline::set_volume(Cookie::Float vol, Cookie::Int channel)
{
    switch (channel) {
        case 1:
            channel1_->set_volume(vol);
            break;
        default:
            mixer_->set_volume(vol);
            break;
    }
}