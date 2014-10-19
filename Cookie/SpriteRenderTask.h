//
//  SpriteRenderTask.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__SpriteRenderTask__
#define __Cookie__SpriteRenderTask__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "RenderTask.h"

namespace Cookie {
    class SpriteRenderTask : public RenderTask
    {
    public:
        SpriteRenderTask();
        virtual ~SpriteRenderTask();
        virtual void render(Cookie::Point origin) const;
        
    public:
        const Cookie::Sprite* sprite;
        Cookie::Rect src_rect;
        SDL_Surface* dst_surface;
        Cookie::Rect dst_rect;
    };
}

#endif /* defined(__Cookie__SpriteRenderTask__) */
