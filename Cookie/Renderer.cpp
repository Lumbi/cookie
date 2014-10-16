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
    camera_ = NULL;
}

void Cookie::Renderer::set_camera(Cookie::Camera* camera)
{
    camera_ = camera;
}

void Cookie::Renderer::addToBatch(Cookie::Sprite& spr, Cookie::Point pos, Cookie::Float depth)
{
    sprite_batch_.push({depth, &spr, spr.size(), spr.size() + pos});
}

void Cookie::Renderer::renderBatch()
{
    SDL_FillRect(sdl_surface_, NULL, 0x000000);
    
    Cookie::Point offset = {0,0};
    if(camera_ != NULL)
    {
        offset += { camera_->viewport().w /2.0f, camera_->viewport().h/2.0f };
        offset -= camera_->position_world();
    }
    
    while(!sprite_batch_.empty())
    {
        const RenderTask& task = sprite_batch_.top();
        
        SDL_Rect sdl_src = Cookie::convert(task.src);
        SDL_Rect sdl_dst = Cookie::convert(task.dst + offset);
        SDL_BlitSurface(task.sprite->sdl_surface(),
                        &sdl_src,
                        sdl_surface_,
                        &sdl_dst
                        );
        
        sprite_batch_.pop();
    }
}