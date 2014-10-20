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
#include "RenderSurfaceTask.h"
#include "RenderTextureTask.h"

Cookie::Renderer::Renderer(SDL_Window* window)
{
    sdl_surface_ = SDL_GetWindowSurface(window);
    sdl_renderer_ = SDL_GetRenderer(window);
    
    if(sdl_renderer_ == NULL)
    {
        printf("Failed to create SDL hardware accelerated renderer: %s\n",SDL_GetError());
    }
    
    camera_ = NULL;
}

Cookie::Renderer::~Renderer()
{
    SDL_FreeSurface(sdl_surface_);
    SDL_DestroyRenderer(sdl_renderer_);
}

SDL_Renderer* Cookie::Renderer::sdl_renderer() const
{
    return sdl_renderer_;
}

SDL_Surface* Cookie::Renderer::sdl_surface() const
{
    return sdl_surface_;
}

void Cookie::Renderer::set_camera(Cookie::Camera* camera)
{
    camera_ = camera;
}

void Cookie::Renderer::addToBatch(Cookie::Rect rect, Cookie::Color color, Cookie::Float depth)
{
    Cookie::RectRenderTask* renderTask = new Cookie::RectRenderTask(this);
    renderTask->rect = rect;
    renderTask->color = color;
    renderTask->depth = depth;
    sprite_batch_.push(renderTask);
}

void Cookie::Renderer::addToBatch(Cookie::Texture& tex, Cookie::Point pos, Cookie::Float depth)
{
    Cookie::RenderTextureTask* renderTask = new Cookie::RenderTextureTask(this);
    renderTask->depth = depth;
    renderTask->texture = &tex;
    renderTask->src_rect = {0,0, tex.width(), tex.height()};
    renderTask->dst_rect = renderTask->src_rect + pos;
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