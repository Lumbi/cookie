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

namespace Cookie
{
    class Game;
    class Physics
    {
    public:
        const Cookie::Vector& gravity() const;
        void set_gravity(Cookie::Vector);
        
        void update(Cookie::Game& game);
        
    private:
        Cookie::Vector gravity_;
        Cookie::Vector velocity_;
    };
}

#endif /* defined(__Cookie__Physics__) */
