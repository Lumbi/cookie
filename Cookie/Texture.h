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
#include <string>
#include "Bool.h"
#include "Color.h"
#include "Int.h"
#include "Point.h"
#include "Rect.h"

namespace Cookie
{
    class Renderer;
    
    typedef enum
    {
        NO_FLIP = SDL_FLIP_NONE,
        FLIP_X = SDL_FLIP_HORIZONTAL,
        FLIP_Y = SDL_FLIP_VERTICAL,
        FLIP_BOTH = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
    } TextureRenderFlip;
    
    typedef enum
    {
        BLENDMODE_NONE = SDL_BLENDMODE_NONE,
        BLENDMODE_BLEND = SDL_BLENDMODE_BLEND,
        BLENDMODE_ADD = SDL_BLENDMODE_ADD,
        BLENDMODE_MOD = SDL_BLENDMODE_MOD
    } TextureBlendMode;
    
    class Texture
    {
    public:
        Texture();
        virtual ~Texture();

        Cookie::Bool open(std::string path, const Cookie::Renderer* renderer = NULL);

        Cookie::Int width() const;
        Cookie::Int height() const;
        
        void set_color(Cookie::Color);
        void set_blend_mode(Cookie::TextureBlendMode);
        void set_alpha(Cookie::Float);
        
        void render(Cookie::Renderer* renderer,
                    const Cookie::Rect* src_rect = NULL,
                    const Cookie::Rect* dst_rect = NULL,
                    Cookie::TextureRenderFlip flip = NO_FLIP,
                    Cookie::Float angle = 0,
                    const Cookie::Point* center = NULL);
        
    private:
        void free();
        
    private:
        SDL_Texture* sdl_texture_;
        Cookie::Int width_;
        Cookie::Int height_;
    };
}

#endif /* defined(__Cookie__Texture__) */
