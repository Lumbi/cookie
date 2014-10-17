//
//  Renderer.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Renderer__
#define __Cookie__Renderer__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <queue>
#include <utility>
#include "Texture.h"
#include "Sprite.h"
#include "Point.h"
#include "Rect.h"
#include "RenderTask.h"
#include "Camera.h"

namespace Cookie
{
    class Renderer
    {
    public:
        Renderer(SDL_Surface*);
        
        void set_camera(Cookie::Camera*);
        
        // Drawing Primitives
        
        void addToBatch(Cookie::Rect rect, Cookie::Color color, Cookie::Float depth=0);
        
        // Drawing Sprites
        
        void addToBatch(Cookie::Sprite& spr, Cookie::Point pos, Cookie::Float depth=0);
        void addToBatch(Cookie::Sprite& spr, Cookie::Rect srcRect, Cookie::Point pos, Cookie::Float depth=0);
        void addToBatch(Cookie::Sprite& spr, Cookie::Rect srcRect, Cookie::Rect dstRect, Cookie::Float depth=0);
        
        void renderBatch();
        
    private:
        SDL_Surface* sdl_surface_;
        Camera* camera_;
        std::priority_queue<Cookie::RenderTask*> sprite_batch_;
    };
}

#endif /* defined(__Cookie__Renderer__) */
