//
//  Physics.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-16.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Physics__
#define __Cookie__Physics__

#include <stdio.h>
#include <vector>
#include "Vector.h"
#include "Node.h"
#include "CollisionHandler.h"
#include "RectBody.h"
#include "CircleBody.h"

namespace Cookie
{
    class Game;
    
    class Physics
    {
    public:
        Physics();
        virtual ~Physics();
        
        const Cookie::Vector& gravity() const;
        void set_gravity(Cookie::Vector);
        
        void update(Cookie::Game& game);
        
        void add_collision_handler(Cookie::CollisionHandler* const);
        void remove_collision_handler(const Cookie::CollisionHandler* const);
        
    private:
        Cookie::Bool resolve_collision(Cookie::Node* nodeA, Cookie::Node* nodeB);
        Cookie::Bool resolve_collision(Cookie::RectBody& bodyA, Cookie::RectBody& bodyB);
        Cookie::Bool resolve_collision(Cookie::RectBody& bodyA, Cookie::CircleBody& bodyB);
        Cookie::Bool resolve_collision(Cookie::CircleBody& bodyA, Cookie::CircleBody& bodyB);
        void push_collision(Cookie::PhysicsBody*, Cookie::PhysicsBody*);
        void notify_collision_handlers();
        
    public:
        
    private:
        Cookie::Vector gravity_;
        std::vector<Cookie::CollisionHandler*> collision_handlers_;
        std::vector<Cookie::Collision> collisions_;
    };
}

#endif /* defined(__Cookie__Physics__) */
