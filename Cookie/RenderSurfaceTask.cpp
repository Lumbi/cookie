//
//  RenderSurfaceTask.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "RenderSurfaceTask.h"
#include "SDL_Conversion.h"
#include <SDL2/SDL.h>
#include "Renderer.h"

Cookie::RenderSurfaceTask::RenderSurfaceTask(Cookie::Renderer* renderer) : Cookie::RenderTask(renderer)
{
    surface = NULL;
}

Cookie::RenderSurfaceTask::~RenderSurfaceTask()
{
    
}

void Cookie::RenderSurfaceTask::render(Cookie::Point origin) const
{
    if(surface == NULL) return;
    
    SDL_Rect sdl_src_rect = Cookie::convert(src_rect);
    SDL_Rect sdl_dst_rect = Cookie::convert(dst_rect + origin);
    
    SDL_BlitSurface(surface,
                    &sdl_src_rect,
                    renderer_->sdl_surface(),
                    &sdl_dst_rect
                    );
}