//
//  PhysicsBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "PhysicsBlock.h"
#include "Vector.h"
#include "Game.h"

Cookie::PhysicsBlock::PhysicsBlock(const Physics* physics) : Cookie::Block()
{
    physics_ = physics;
    active_ = true;
}

void Cookie::PhysicsBlock::update(Cookie::Node& node, Cookie::Game& game)
{
    if(active_)
    {
        velocity_ += (game.time_elapsed()/1000.0f) * physics_->gravity();
        node.translate_by(velocity_.x, velocity_.y);
    }
}

const Cookie::Vector& Cookie::PhysicsBlock::velocity() const
{
    return velocity_;
}

void Cookie::PhysicsBlock::set_velocity(Cookie::Vector velocity)
{
    velocity_ = velocity;
}