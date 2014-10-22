//
//  AudioFilter.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__AudioFilter__
#define __Cookie__AudioFilter__

#include <stdio.h>
#include <SDL2/SDL.h>

namespace Cookie
{
    class AudioFilter
    {
    public:
        AudioFilter(SDL_AudioSpec audio_spec);
        virtual ~AudioFilter();
        virtual void process(const Uint8* const data, Uint32 len) = 0;
        Cookie::AudioFilter* const set_output(Cookie::AudioFilter*);
    protected:
        SDL_AudioSpec audio_spec_;
        Cookie::AudioFilter* out_;
    };
}

#endif /* defined(__Cookie__AudioFilter__) */
