//
//  Collision.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-27.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Collision__
#define __Cookie__Collision__

#include <stdio.h>

namespace Cookie
{
    class PhysicsBody;
    
    typedef struct
    {
        Cookie::PhysicsBody* bodyA;
        Cookie::PhysicsBody* bodyB;
    } Collision;
}

#endif /* defined(__Cookie__Collision__) */
