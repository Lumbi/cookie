//
//  RenderAnimTask.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__RenderAnimTask__
#define __Cookie__RenderAnimTask__

#include <stdio.h>
#include "RenderTask.h"
#include "Animation.h"
#include "Point.h"

namespace Cookie
{
    class RenderAnimTask : public RenderTask
    {
    public:
        RenderAnimTask(Cookie::Renderer*, Cookie::Animation*);
        virtual ~RenderAnimTask();
        
        virtual void render(Cookie::Point origin) const;

    public:
        Cookie::Point position;
        
    protected:
        Cookie::Animation* animation_;
    };
}

#endif /* defined(__Cookie__RenderAnimTask__) */
