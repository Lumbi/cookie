//
//  RenderTextureTask.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "RenderTextureTask.h"
#include "SDL_Conversion.h"
#include <SDL2/SDL.h>
#include "Renderer.h"

Cookie::RenderTextureTask::RenderTextureTask(Cookie::Renderer* renderer) : Cookie::RenderTask(renderer)
{
    texture = NULL;
}

Cookie::RenderTextureTask::~RenderTextureTask()
{
}

void Cookie::RenderTextureTask::render(Cookie::Point origin) const
{
    if(texture == NULL) return;
    
    Cookie::Rect off_dst_rect = dst_rect + origin;
    texture->render(renderer_, &src_rect, &off_dst_rect);
}