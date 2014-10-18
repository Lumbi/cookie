//
//  CircleBody.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__CircleBody__
#define __Cookie__CircleBody__

#include <stdio.h>
#include "PhysicsBody.h"

namespace Cookie {
    class CircleBody : public PhysicsBody
    {
    public:
        CircleBody();
        virtual ~CircleBody();
        virtual PhysicsBodyType body_type() const { return Cookie::CircleBodyType; };
        
        Cookie::Float radius() const;
        void set_radius(Cookie::Float);
        
    protected:
        Cookie::Float radius_;
    };
}

#endif /* defined(__Cookie__CircleBody__) */
