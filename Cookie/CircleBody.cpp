//
//  CircleBody.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-27.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "CircleBody.h"

Cookie::CircleBody::CircleBody()
{
    circle_ = {{0,0},0};
}

Cookie::CircleBody::~CircleBody()
{
}

Cookie::Circle Cookie::CircleBody::circle() const
{
    return circle_;
}

void Cookie::CircleBody::set_circle(Cookie::Circle circle)
{
    circle_ = circle;
}

void Cookie::CircleBody::set_radius(Cookie::Float radius)
{
    circle_.radius = radius;
}