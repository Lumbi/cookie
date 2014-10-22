//
//  AudioPipeline.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__AudioPipeline__
#define __Cookie__AudioPipeline__

#include <stdio.h>
#include "AudioFilter.h"
#include "AudioVolumeFilter.h"
#include "AudioMixFilter.h"
#include "Float.h"
#include "Int.h"

namespace Cookie
{
    typedef void (*AudioPipelineCallback)(Uint8* data, Uint32 len);
    
    class AudioPipeline : private AudioFilter
    {
    public:
        AudioPipeline(SDL_AudioSpec audio_spec, Cookie::AudioPipelineCallback);
        virtual ~AudioPipeline();
        
        void push(Uint8* data, Uint32 len, Cookie::Int channel = 0);
        void flush();
        
        void set_volume(Cookie::Float vol, Cookie::Int channel = 0);

    private:
        virtual void process(const Uint8* const data, Uint32 len);
        
    private:
        Cookie::AudioPipelineCallback callback_;
        Cookie::AudioVolumeFilter* channel1_;
        Cookie::AudioMixFilter* mixer_;
    };
}

#endif /* defined(__Cookie__AudioPipeline__) */
