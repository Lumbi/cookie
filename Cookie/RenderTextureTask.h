//
//  RenderTextureTask.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__RenderTextureTask__
#define __Cookie__RenderTextureTask__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "RenderTask.h"

namespace Cookie
{
    class RenderTextureTask : public Cookie::RenderTask
    {
    public:
        RenderTextureTask(Cookie::Renderer*);
        virtual ~RenderTextureTask();
        virtual void render(Cookie::Point origin) const;
        
    public:
        SDL_Texture* texture;
        Cookie::Rect src_rect;
        Cookie::Rect dst_rect;
    };

}

#endif /* defined(__Cookie__RenderTextureTask__) */
