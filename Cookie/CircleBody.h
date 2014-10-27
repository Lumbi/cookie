
//
//  CircleBody.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-27.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__CircleBody__
#define __Cookie__CircleBody__

#include <stdio.h>
#include "PhysicsBody.h"
#include "Circle.h"

namespace Cookie
{
    class CircleBody : public PhysicsBody
    {
    public:
        CircleBody();
        ~CircleBody();
        PhysicsBodyType body_type() const {return CIRCLE_BODY; };
        
        Cookie::Circle circle() const;
        void set_circle(Cookie::Circle);
        
        void set_radius(Cookie::Float);
        
    private:
        Cookie::Circle circle_;
    };
    
}

#endif /* defined(__Cookie__CircleBody__) */
