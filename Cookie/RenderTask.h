//
//  RenderTask.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__RenderTask__
#define __Cookie__RenderTask__

#include <stdio.h>
#include "Sprite.h"
#include "Float.h"
#include "Color.h"

namespace Cookie
{
    class Renderer;
    class RenderTask
    {
    public:
        RenderTask(Cookie::Renderer*);
        virtual ~RenderTask() {};
        Cookie::Float depth;
        Cookie::Color color;
        //TODO: add surface here
        
        virtual void render(Cookie::Point origin) const = 0;
        
    protected:
        Cookie::Renderer* renderer_;
        
    };
    
    bool operator<(const Cookie::RenderTask& lhs, const Cookie::RenderTask& rhs);
    
}

#endif /* defined(__Cookie__RenderTask__) */
