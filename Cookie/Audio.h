//
//  Audio.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Audio__
#define __Cookie__Audio__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Sound.h"

namespace Cookie
{
    class Audio
    {
    public:
        Audio();
        virtual ~Audio();
        
        void init();
        
    private:
        SDL_AudioDeviceID device_;
    };
}

#endif /* defined(__Cookie__Audio__) */
