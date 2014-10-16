//
//  World.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "World.h"

Cookie::World::World()
{
    physics_.set_gravity({0,9.8});
    camera_ = new Camera();
}

const Cookie::Physics& Cookie::World::physics() const
{
    return physics_;
}

Cookie::Camera* Cookie::World::camera() const
{
    return camera_;
}