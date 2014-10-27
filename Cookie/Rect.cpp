//
//  Rect.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Rect.h"
#include "Circle.h"
#include <cmath>

Cookie::Rect& Cookie::Rect::operator+=(const Cookie::Point& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Cookie::Bool Cookie::Rect::intersects(const Cookie::Rect& other) const
{
    if (x+w <= other.x ||
        y+h <= other.y ||
        x >= other.x+other.w ||
        y >= other.y+other.h)
    {
        return false;
    }
    return true;
}

Cookie::Bool Cookie::Rect::intersects(const Cookie::Circle& other) const
{
    if (other.center.x + other.radius <= x ||
        other.center.y + other.radius <= y ||
        other.center.x - other.radius >= x + w ||
        other.center.y - other.radius >= y + h)
    {
        return false;
    }
    return true;
}

Cookie::Vector Cookie::Rect::penetration(const Cookie::Rect& other) const
{
    Cookie::Vector p;
    Cookie::Float right = (other.x+other.w) - x;
    Cookie::Float left = other.x - (x+w);
    Cookie::Float top = other.y - (y+h);
    Cookie::Float bottom = other.y - (y+h);

    if(fabsf(left) < right)
    {
        p.x = left;
    }else{
        p.x = right;
    }
    
    if(fabsf(top) < bottom)
    {
        p.y = top;
    }else{
        p.y = bottom;
    }
    
    if(fabsf(p.x) < fabsf(p.y))
    {
        p.y = 0;
    }else{
        p.x = 0;
    }
    return p;
}

Cookie::Vector Cookie::Rect::penetration(const Cookie::Circle& other) const
{
    Cookie::Vector p;
    Cookie::Float right = (x+w) - (other.center.x - other.radius);
    Cookie::Float left = x - (other.center.x + other.radius);
    Cookie::Float top = y - (other.center.y + other.radius);
    Cookie::Float bottom = (y+h) - (other.center.y - other.radius);
    
    if(fabsf(left) < right)
    {
        p.x = left;
    }else{
        p.x = right;

    }
    
    if(fabsf(top) < bottom)
    {
        p.y = top;
    }else{
        p.y = bottom;
    }
    
    if(fabsf(p.x) < fabsf(p.y))
    {
        p.y = 0;
    }else{
        p.x = 0;
    }
    return p;
}

Cookie::Rect Cookie::Rect::centered_rect() const
{
    return { x-w/2.0f, y-h/2.0f, w, h};
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