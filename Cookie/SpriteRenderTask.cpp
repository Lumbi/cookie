//
//  SpriteRenderTask.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "SpriteRenderTask.h"
#include "SDL_Conversion.h"
#include <SDL2/SDL.h>

Cookie::SpriteRenderTask::SpriteRenderTask() : Cookie::RenderTask()
{
    sprite = NULL;
    dst_surface = NULL;
}

Cookie::SpriteRenderTask::~SpriteRenderTask()
{
    
}

void Cookie::SpriteRenderTask::render(Cookie::Point origin) const
{
    if(sprite != NULL && dst_surface != NULL)
    {
        SDL_Rect sdl_src_rect = Cookie::convert(src_rect);
        SDL_Rect sdl_dst_rect = Cookie::convert(dst_rect + origin);
        
        SDL_BlitSurface(sprite->sdl_surface(),
                        &sdl_src_rect,
                        dst_surface,
                        &sdl_dst_rect
                        );
    }
}