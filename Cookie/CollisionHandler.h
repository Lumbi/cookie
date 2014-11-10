//
//  CollisionHandler.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-11-09.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__CollisionHandler__
#define __Cookie__CollisionHandler__

#include <stdio.h>
#include "Collision.h"

namespace Cookie
{   
    class CollisionHandler
    {
    public:
        CollisionHandler();
        virtual ~CollisionHandler();
        
        virtual void handleCollision(Cookie::Collision&) = 0;
    };
    
    bool operator==(const Cookie::CollisionHandler& lhs, const Cookie::CollisionHandler& rhs);
}

#endif /* defined(__Cookie__CollisionHandler__) */
