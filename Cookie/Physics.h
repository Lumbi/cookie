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
#include "Vector.h"
#include "Node.h"

namespace Cookie
{
    class Game;
    
    class RectBody;
    class CircleBody;
    
    class Physics
    {
    public:
        const Cookie::Vector& gravity() const;
        void set_gravity(Cookie::Vector);
        
        void update(Cookie::Game& game);
        
    private:
        void resolve_collision(Cookie::RectBody& bodyA, Cookie::RectBody& bodyB);
        void resolve_collision(Cookie::RectBody& bodyA, Cookie::CircleBody& bodyB);
        void resolve_collision(Cookie::CircleBody& bodyA, Cookie::CircleBody& bodyB);
        
    private:
        Cookie::Vector gravity_;
        Cookie::Vector velocity_;
    };
}

#endif /* defined(__Cookie__Physics__) */
