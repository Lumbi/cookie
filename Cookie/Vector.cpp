//
//  Vector.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Vector.h"
#include <math.h>

Cookie::Vector& Cookie::Vector::operator+=(const Cookie::Float& rhs)
{
    x += rhs;
    y += rhs;
    return *this;
}

Cookie::Vector& Cookie::Vector::operator-=(const Cookie::Float& rhs)
{
    x -= rhs;
    y -= rhs;
    return *this;
}

Cookie::Vector& Cookie::Vector::operator*=(const Cookie::Float& rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

Cookie::Vector& Cookie::Vector::operator+=(const Cookie::Vector& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Cookie::Vector& Cookie::Vector::operator-=(const Cookie::Vector& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Cookie::Float Cookie::Vector::length()
{
    return sqrt(x*x+y*y);
}

Cookie::Vector Cookie::Vector::unit()
{
    Cookie::Float l = length();
    return { x/l, y/l };
}

bool Cookie::operator==(const Cookie::Vector& lhs, const Cookie::Vector& rhs)
{
    return lhs.x == rhs.y && lhs.x == rhs.y;
}

bool Cookie::operator!=(const Cookie::Vector& lhs, const Cookie::Vector& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

Cookie::Vector Cookie::operator+(const Cookie::Vector& lhs, const Cookie::Vector& rhs)
{
    return { lhs.x+rhs.x , lhs.x+rhs.y };
}

Cookie::Vector Cookie::operator-(const Cookie::Vector& lhs, const Cookie::Vector& rhs)
{
    return { lhs.x-rhs.x , lhs.x-rhs.y };
}

Cookie::Vector Cookie::operator*(const Cookie::Vector& lhs, const Cookie::Float& rhs)
{
    return { lhs.x * rhs, lhs.y * rhs };
}

Cookie::Vector Cookie::operator*(const Cookie::Float& lhs, const Cookie::Vector& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y };
}