//
//  Circle.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-27.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Circle.h"
#include <cmath>

Cookie::Circle& Cookie::Circle::operator+=(const Cookie::Point& rhs)
{
    center += rhs;
    return *this;
}

Cookie::Bool Cookie::Circle::intersects(const Cookie::Circle& other) const
{
    return
    fabsf(center.x - other.center.x) < radius + other.radius &&
    fabsf(center.y - other.center.y) < radius + other.radius;
}

Cookie::Vector Cookie::Circle::penetration(const Cookie::Circle& other) const
{
    Cookie::Float dx = other.center.x - center.x;
    Cookie::Float dy = other.center.y - center.y;
    Cookie::Float d = sqrtf((dx*dx)+(dy*dy));
    Vector p = { -dx, -dy };
    return (radius + other.radius - d) * p.unit();
}

Cookie::Circle Cookie::operator+(const Cookie::Circle& lhs, const Cookie::Point& rhs)
{
    return { lhs.center + rhs, lhs.radius };
}