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
#include <SDL2/SDL_opengl.h>
#include "RenderTask.h"
#include "RectRenderTask.h"

Cookie::Renderer::Renderer(SDL_Surface* sdl_surface)
{
    sdl_surface_ = sdl_surface;
    camera_ = NULL;
}

void Cookie::Renderer::set_camera(Cookie::Camera* camera)
{
    camera_ = camera;
}

void Cookie::Renderer::addToBatch(Cookie::Rect rect, Cookie::Color color, Cookie::Float depth)
{
    Cookie::RectRenderTask* renderTask = new Cookie::RectRenderTask();
    renderTask->rect = rect;
    renderTask->color = color;
    renderTask->depth = depth;
    sprite_batch_.push(renderTask);
}

void Cookie::Renderer::addToBatch(Cookie::Sprite& spr, Cookie::Point pos, Cookie::Float depth)
{
//    sprite_batch_.push({depth, &spr, spr.size(), spr.size() + pos});
}

void Cookie::Renderer::renderBatch()
{   
    Cookie::Point offset = {0,0};
    if(camera_ != NULL)
    {
        offset += { camera_->viewport().w /2.0f, camera_->viewport().h/2.0f };
        offset -= camera_->position_world();
    }
    
    while(!sprite_batch_.empty())
    {
        const RenderTask* task = sprite_batch_.top();
        
        task->render(offset);
        
//        SDL_Rect sdl_src = Cookie::convert(task.src);
//        SDL_Rect sdl_dst = Cookie::convert(task.dst + offset);
//        SDL_BlitSurface(task.sprite->sdl_surface(),
//                        &sdl_src,
//                        sdl_surface_,
//                        &sdl_dst
//                        );
        
        delete task;
        sprite_batch_.pop();
    }
}