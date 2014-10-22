
//
//  AudioMixFilter.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__AudioMixFilter__
#define __Cookie__AudioMixFilter__

#include <stdio.h>
#include <vector>
#include "AudioVolumeFilter.h"

namespace Cookie
{
    class AudioMixFilter  : public AudioVolumeFilter
    {
    public:
        AudioMixFilter(SDL_AudioSpec audio_spec);
        virtual ~AudioMixFilter();
        virtual void process(const Uint8* const buf, Uint32 len);
        void flush();
    private:
        Uint8* acc_buffer_;
        Uint32 acc_len_;
    };
}

#endif /* defined(__Cookie__AudioMixFilter__) */
