//
//  RenderSurfaceTask.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__RenderSurfaceTask__
#define __Cookie__RenderSurfaceTask__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "RenderTask.h"

namespace Cookie {
    class RenderSurfaceTask : public Cookie::RenderTask
    {
    public:
        RenderSurfaceTask(Cookie::Renderer*);
        virtual ~RenderSurfaceTask();
        virtual void render(Cookie::Point origin) const;
        
    public:
        SDL_Surface* surface;
        Cookie::Rect src_rect;
        Cookie::Rect dst_rect;
    };
}

#endif /* defined(__Cookie__RenderSurfaceTask__) */
