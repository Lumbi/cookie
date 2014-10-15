//
//  Texture.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Texture__
#define __Cookie__Texture__

#include <stdio.h>
#include <SDL2/SDL.h>

namespace Cookie
{
    class Texture
    {
    public:
        Texture(SDL_Texture*);
    private:
        SDL_Texture* sdl_texture_;
    };
}

#endif /* defined(__Cookie__Texture__) */
