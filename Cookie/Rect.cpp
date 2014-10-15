//
//  Rect.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Rect.h"

Cookie::Rect& Cookie::Rect::operator+=(const Cookie::Point& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

bool Cookie::operator==(const Cookie::Rect& lhs, const Cookie::Rect& rhs)
{
    return
    lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.w == rhs.w &&
    lhs.h == rhs.h;
}

bool Cookie::operator!=(const Cookie::Rect& lhs, const Cookie::Rect& rhs)
{
    return !(lhs==rhs);
}

Cookie::Rect Cookie::operator+(const Cookie::Rect& lhs, const Cookie::Point& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.w,
        lhs.h
    };
}