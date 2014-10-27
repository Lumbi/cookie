//
//  Point.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Point.h"

Cookie::Point Cookie::Point::rotate_by(Cookie::Float degrees) const
{
#warning TODO: implement rotation
    return { 0, 0 };
}

Cookie::Point Cookie::Point::rotate_to(Cookie::Float degrees) const
{
    #warning TODO: implement rotation
    return { 0,0 };
}

Cookie::Point& Cookie::Point::operator+=(const Cookie::Point& rhs)
{
    x+=rhs.x;
    y+=rhs.y;
    return *this;
}

Cookie::Point& Cookie::Point::operator-=(const Cookie::Point& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
    return *this;
}

Cookie::Point Cookie::operator+(Cookie::Point lhs, const Cookie::Point& rhs)
{
    return { lhs.x+rhs.x , lhs.y+rhs.y };
}

Cookie::Point Cookie::operator-(Cookie::Point lhs, const Cookie::Point& rhs)
{
    return { lhs.x-rhs.x , lhs.y-rhs.y };
}

Cookie::Point operator*(Cookie::Point lhs, const Cookie::Float& rhs)
{
    return { lhs.x*rhs, lhs.y*rhs };
}

Cookie::Point operator/(Cookie::Point lhs, const Cookie::Float& rhs)
{
    return { lhs.x/rhs, lhs.y/rhs };
}

Cookie::Point operator*(Cookie::Float lhs, const Cookie::Point& rhs)
{
    return { lhs*rhs.x, lhs*rhs.y };
}

Cookie::Point operator/(Cookie::Float lhs, const Cookie::Point& rhs)
{
    return { lhs/rhs.x, lhs/rhs.y };
}
