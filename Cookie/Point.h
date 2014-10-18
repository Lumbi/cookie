//
//  Point.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Point__
#define __Cookie__Point__

#include <stdio.h>
#include "Float.h"

namespace Cookie
{
    typedef struct Point
    {
        Cookie::Float x;
        Cookie::Float y;
        
        Cookie::Point rotate_to(Cookie::Float degrees) const;
        Cookie::Point rotate_by(Cookie::Float degrees) const;
        
        Cookie::Point& operator+=(const Cookie::Point& rhs);
        Cookie::Point& operator-=(const Cookie::Point& rhs);
        
    } Point;

    Cookie::Point operator+(Cookie::Point lhs, const Cookie::Point& rhs);
    Cookie::Point operator-(Cookie::Point lhs, const Cookie::Point& rhs);
    
    Cookie::Point operator*(Cookie::Point lhs, const Cookie::Float& rhs);
    Cookie::Point operator/(Cookie::Point lhs, const Cookie::Float& rhs);
    Cookie::Point operator*(Cookie::Float lhs, const Cookie::Point& rhs);
    Cookie::Point operator/(Cookie::Float lhs, const Cookie::Point& rhs);
}

#endif /* defined(__Cookie__Point__) */
