//
//  CircleBody.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "CircleBody.h"

Cookie::CircleBody::CircleBody() : PhysicsBody()
{
    radius_ = 1;
}

Cookie::CircleBody::~CircleBody()
{
}

Cookie::Float Cookie::CircleBody::radius() const
{
    return radius_;
}

void Cookie::CircleBody::set_radius(Cookie::Float radius)
{
    radius_ = radius;
}