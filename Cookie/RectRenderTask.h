//
//  RectRenderTask.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__RectRenderTask__
#define __Cookie__RectRenderTask__

#include <stdio.h>
#include "RenderTask.h"
#include "Rect.h"
#include "Point.h"
#include "Color.h"

namespace Cookie {
    class RectRenderTask : public RenderTask
    {
    public:
        RectRenderTask(Cookie::Renderer*);
        virtual ~RectRenderTask();
        Cookie::Rect rect;
        Cookie::Color color;
        
        virtual void render(Cookie::Point origin) const;
    };
}

#endif /* defined(__Cookie__RectRenderTask__) */
