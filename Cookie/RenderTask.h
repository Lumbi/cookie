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

namespace Cookie
{
    typedef struct
    {
        Cookie::Float depth;
        Cookie::Sprite* sprite;
        Cookie::Rect src;
        Cookie::Rect dst;
    } RenderTask;
    
    bool operator<(const Cookie::RenderTask& lhs, const Cookie::RenderTask& rhs);
}

#endif /* defined(__Cookie__RenderTask__) */
