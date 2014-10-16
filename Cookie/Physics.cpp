//
//  Physics.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-16.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Physics.h"

const Cookie::Vector& Cookie::Physics::gravity() const
{
    return gravity_;
}

void Cookie::Physics::set_gravity(Cookie::Vector gravity)
{
    gravity_ = gravity;
}