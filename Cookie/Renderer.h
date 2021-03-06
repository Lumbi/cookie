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
#include "Point.h"
#include "Rect.h"
#include "RenderTask.h"
#include "Camera.h"
#include "Texture.h"
#include "Animation.h"

namespace Cookie
{
    class Renderer
    {
    public:
        Renderer(SDL_Window*);
        virtual ~Renderer();
        
        SDL_Renderer* sdl_renderer() const;
        SDL_Surface* sdl_surface() const;
        
        void set_camera(Cookie::Camera*);
        
#pragma mark - Drawing Primitives
        
        void addToBatch(Cookie::Rect rect, Cookie::Color color, Cookie::Float depth=0);
        
#pragma mark - Drawing Textures
        
        void addToBatch(Cookie::Texture& tex, Cookie::Point pos, Cookie::Float depth=0);
//        void addToBatch(Cookie::Texture& tex, Cookie::Rect srcRect, Cookie::Point pos, Cookie::Float depth=0);
//        void addToBatch(Cookie::Texture& tex, Cookie::Rect srcRect, Cookie::Rect dstRect, Cookie::Float depth=0);
        
#pragma mark - Drawing Animatons
        
        void addToBatch(Cookie::Animation& anim, Cookie::Point pos, Cookie::Float depth = 0);
        
        void renderBatch();
        
    private:
        SDL_Renderer* sdl_renderer_;
        SDL_Surface* sdl_surface_;
        Camera* camera_;
        std::priority_queue<Cookie::RenderTask*> sprite_batch_;
    };
}

#endif /* defined(__Cookie__Renderer__) */
