//
//  AudioPipeline.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioPipeline.h"

const int kChannelsSize = 6;

Cookie::AudioPipeline::AudioPipeline(SDL_AudioSpec audio_spec,
                                     Cookie::AudioPipelineCallback callback) : Cookie::AudioFilter(audio_spec)
{
    callback_ = callback;
    
    mixer_ = new Cookie::AudioMixFilter(audio_spec);
    master_volume_ = new Cookie::AudioVolumeFilter(audio_spec);
    
    for(int i = 0; i < kChannelsSize; ++i)
    {
        Cookie::AudioVolumeFilter* channel;
        channel = new Cookie::AudioVolumeFilter(audio_spec);
        channel->set_output(mixer_);
        channels_.push_back(channel);
    }

    mixer_->set_output(master_volume_);
    master_volume_->set_output(this);
}

Cookie::AudioPipeline::~AudioPipeline()
{
    for(auto it = channels_.begin(); it != channels_.end(); ++it)
    {
        delete *it;
    }
    delete mixer_;
}

void Cookie::AudioPipeline::push(Uint8* data, Uint32 len, Cookie::Int channel)
{
    if(channel < 0 || channel > kChannelsSize)
    {
        channel = get_next_channel();
    }
    
    Cookie::AudioBuffer buffer;
    buffer.data = data;
    buffer.len = len;
    buffer.channel = channel;
    
    audio_buffers_.push_back(buffer);
}

void Cookie::AudioPipeline::flush()
{
    while (!this->audio_buffers_.empty())
    {
        const Cookie::AudioBuffer& buffer = this->audio_buffers_.front();
        if(buffer.channel > 0 && buffer.channel <= kChannelsSize)
        {
            channels_[buffer.channel-1]->process(buffer.data, buffer.len);
        }
        this->audio_buffers_.pop_front();
    }
    
    this->mixer_->flush();
}

Cookie::Int Cookie::AudioPipeline::get_next_channel()
{
    static int next_channel = 0;
    ++next_channel;
    return next_channel % (kChannelsSize-1) + 1;
}

void Cookie::AudioPipeline::process(const Uint8* const data, Uint32 len)
{
    if(len != 0)
    {
        callback_(data, len, userdata);
    }
}

void Cookie::AudioPipeline::set_volume(Cookie::Float vol, Cookie::Int channel)
{
    if(channel > 0 && channel <= kChannelsSize){
        channels_[channel-1]->set_volume(vol);
    }else{
        master_volume_->set_volume(vol);
    }
}
