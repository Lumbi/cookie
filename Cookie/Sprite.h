//
//  Sprite.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Sprite__
#define __Cookie__Sprite__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Rect.h"

namespace Cookie
{
    class Sprite
    {
    public:
        Sprite(SDL_Surface*);
        
        SDL_Surface* sdl_surface() const;
        Cookie::Rect size() const;
        
    private:
        SDL_Surface* sdl_surface_;
        
    };
}

#endif /* defined(__Cookie__Sprite__) */
