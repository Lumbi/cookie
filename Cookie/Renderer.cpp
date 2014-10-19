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
#include "SpriteRenderTask.h"

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
    Cookie::SpriteRenderTask* renderTask = new Cookie::SpriteRenderTask();
    renderTask->depth = depth;
    renderTask->sprite = &spr;
    renderTask->dst_surface = sdl_surface_;
    renderTask->src_rect = spr.size();
    renderTask->dst_rect = spr.size() + pos;
    sprite_batch_.push(renderTask);
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
        
        delete task;
        sprite_batch_.pop();
    }
}