//
//  AudioVolumeFilter.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__AudioVolumeFilter__
#define __Cookie__AudioVolumeFilter__

#include <stdio.h>
#include "AudioFilter.h"
#include "Float.h"

namespace Cookie
{
    class AudioVolumeFilter : public AudioFilter
    {
    public:
        AudioVolumeFilter(SDL_AudioSpec audio_spec, Cookie::Float volume = 1.0f);
        virtual ~AudioVolumeFilter();
        virtual void process(const Uint8* const buf, Uint32 len);
        void set_volume(Cookie::Float);
    protected:
        Cookie::Float volume_;
    };
}

#endif /* defined(__Cookie__AudioVolumeFilter__) */
