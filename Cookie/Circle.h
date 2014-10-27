//
//  Circle.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-27.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Circle__
#define __Cookie__Circle__

#include <stdio.h>
#include "Float.h"
#include "Point.h"
#include "Bool.h"
#include "Vector.h"

namespace Cookie
{
    typedef struct Circle
    {
        Cookie::Point center;
        Cookie::Float radius;
        
        Cookie::Circle& operator+=(const Cookie::Point& rhs);
        
        Cookie::Bool intersects(const Cookie::Circle&) const;
        Cookie::Vector penetration(const Cookie::Circle&) const;
        
    }Circle;
    
    Cookie::Circle operator+(const Cookie::Circle& lhs, const Cookie::Point& rhs);
    
}

#endif /* defined(__Cookie__Circle__) */
