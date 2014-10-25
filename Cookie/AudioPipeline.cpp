//
//  AudioPipeline.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioPipeline.h"

SDL_Thread* audio_pipeline_thread;
int Cookie::audio_pipeline_thread_func (void * data)
{
    auto audio_pipeline = static_cast<Cookie::AudioPipeline*>(data);
    
    while (audio_pipeline != NULL)
    {
        if(!audio_pipeline->audio_buffers_.empty())
        {
            const Cookie::AudioBuffer& buffer = audio_pipeline->audio_buffers_.front();
            switch (buffer.channel) {
                case 1:
                    audio_pipeline->channel1_->process(buffer.data, buffer.len);
                    break;
                default:
                    audio_pipeline->mixer_->flush();
                    break;
            }
            audio_pipeline->audio_buffers_.pop_front();
        }
    }
    return 0;
}

Cookie::AudioPipeline::AudioPipeline(SDL_AudioSpec audio_spec,
                                     Cookie::AudioPipelineCallback callback) : Cookie::AudioFilter(audio_spec)
{
    callback_ = callback;
    
    channel1_ = new Cookie::AudioVolumeFilter(audio_spec);
    mixer_ = new Cookie::AudioMixFilter(audio_spec);
    master_volume_ = new Cookie::AudioVolumeFilter(audio_spec);
    
    channel1_->set_output(mixer_);
    
    mixer_->set_output(master_volume_);
    master_volume_->set_output(this);
    
//    audio_pipeline_thread = SDL_CreateThread(audio_pipeline_thread_func, "CookieAudioPipelineThread", this);
}

Cookie::AudioPipeline::~AudioPipeline()
{
//    SDL_DetachThread(audio_pipeline_thread);
    
    delete channel1_;
    delete mixer_;
}

void Cookie::AudioPipeline::push(Uint8* data, Uint32 len, Cookie::Int channel)
{
    static Cookie::Int last_channel = 0;
    static const Cookie::Int channel_size = 1;
    
#warning TODO Support more channels
    
    if(channel == 0)
    {
        //        channel = (last_channel+1) % channel_size;
        channel = 1;
    }
    
    Cookie::AudioBuffer buffer;
    buffer.data = data;
    buffer.len = len;
    buffer.channel = channel;
    
    audio_buffers_.push_back(buffer);
    
    last_channel = channel;
}

void Cookie::AudioPipeline::flush()
{
    while (!this->audio_buffers_.empty())
    {
        const Cookie::AudioBuffer& buffer = this->audio_buffers_.front();
        switch (buffer.channel) {
            case 1:
                this->channel1_->process(buffer.data, buffer.len);
                break;
            default:
                break;
        }
        this->audio_buffers_.pop_front();
    }
    
    this->mixer_->flush();
}

void Cookie::AudioPipeline::process(const Uint8* const data, Uint32 len)
{
    if(len != 0)
    {
        callback_(data, len);
    }
}

void Cookie::AudioPipeline::set_volume(Cookie::Float vol, Cookie::Int channel)
{
    switch (channel) {
        case 1:
            channel1_->set_volume(vol);
            break;
        default:
            master_volume_->set_volume(vol);
            break;
    }
}
