//
//  Renderer.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Renderer.h"
#include "SDL_Conversion.h"
#include "RenderTask.h"
#include "Rect.h"

Cookie::Renderer::Renderer(SDL_Surface* sdl_surface)
{
    sdl_surface_ = sdl_surface;
}

void Cookie::Renderer::addToBatch(Cookie::Sprite& spr, Cookie::Point pos, Cookie::Float depth)
{
    sprite_batch_.push({depth, &spr, spr.size(), spr.size() + pos});
}

void Cookie::Renderer::renderBatch()
{
    while(!sprite_batch_.empty())
    {
        const RenderTask& task = sprite_batch_.top();
        
        SDL_Rect sdl_src = Cookie::convert(task.src);
        SDL_Rect sdl_dst = Cookie::convert(task.dst);
        SDL_BlitSurface(task.sprite->sdl_surface(),
                        &sdl_src,
                        sdl_surface_,
                        &sdl_dst
                        );
        
        sprite_batch_.pop();
    }
}