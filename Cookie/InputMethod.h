//
//  InputMethod.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__InputMethod__
#define __Cookie__InputMethod__

#include <stdio.h>
#include <SDL2/SDL.h>

namespace Cookie
{
    class InputMethod
    {
    public:
        virtual void process_event(SDL_Event&) = 0;
    };
}

#endif /* defined(__Cookie__InputMethod__) */
