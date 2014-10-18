//
//  PhysicsBody.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "PhysicsBody.h"
#include "Node.h"

#pragma mark - Constructors

Cookie::PhysicsBody::PhysicsBody()
{
    node_ = NULL;
    mass_ = 1;
    restitution_ = 0.2f;
    velocity_ = {0,0};
    ignores_gravity_ = false;
    dynamic_ = false;
}

#pragma mark - Destructor

Cookie::PhysicsBody::~PhysicsBody()
{
}

#pragma mark - Accessors & Mutators

Cookie::Bool Cookie::PhysicsBody::dynamic() const
{
    return dynamic_;
}

void Cookie::PhysicsBody::set_dynamic(Cookie::Bool dynamic)
{
    dynamic_ = dynamic;
}

Cookie::Float Cookie::PhysicsBody::mass() const
{
    return mass_;
}

void Cookie::PhysicsBody::set_mass(Cookie::Float mass)
{
    mass_ = mass;
}

Cookie::Float Cookie::PhysicsBody::restitution() const
{
    return restitution_;
}

void Cookie::PhysicsBody::set_restitution(Cookie::Float restitution)
{
    restitution_ = restitution;
}

Cookie::Node* const Cookie::PhysicsBody::node() const
{
    return node_;
}

void Cookie::PhysicsBody::set_node(Cookie::Node* const node)
{
    node_ = node;
    if(node->physics_body() != this)
    {
        node->set_physics_body(this);
    }
}

const Cookie::Vector& Cookie::PhysicsBody::velocity() const
{
    return velocity_;
}

void Cookie::PhysicsBody::set_velocity(Cookie::Vector velocity)
{
    velocity_ = velocity;
}

Cookie::Bool Cookie::PhysicsBody::ignores_gravity() const
{
    return ignores_gravity_;
}

void Cookie::PhysicsBody::set_ignores_gravity(Cookie::Bool ignores_gravity)
{
    ignores_gravity_ = ignores_gravity;
}
