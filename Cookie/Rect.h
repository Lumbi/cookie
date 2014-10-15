//
//  Rect.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Rect__
#define __Cookie__Rect__

#include <stdio.h>
#include <climits>
#include "Int.h"
#include "Float.h"
#include "Point.h"

namespace Cookie
{
    typedef struct Rect
    {
        Cookie::Float x;
        Cookie::Float y;
        Cookie::Float w;
        Cookie::Float h;
        
        Cookie::Rect& operator+=(const Cookie::Point& rhs);
        
    } Rect;
    
    const Cookie::Rect kNullRect = { INT_MIN,INT_MIN,INT_MIN,INT_MIN };
    
    bool operator==(const Cookie::Rect& lhs, const Cookie::Rect& rhs);
    bool operator!=(const Cookie::Rect& lhs, const Cookie::Rect& rhs);
    
    Cookie::Rect operator+(const Cookie::Rect& lhs, const Cookie::Point& rhs);
}

#endif /* defined(__Cookie__Rect__) */
