//
//  PhysicsBody.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__PhysicsBody__
#define __Cookie__PhysicsBody__

#include <stdio.h>
#include "Float.h"
#include "Vector.h"

namespace Cookie
{
    class Node;
    
    typedef enum
    {
        CircleBodyType,
        RectangleBodyType
    } PhysicsBodyType;
    
    class PhysicsBody
    {
    public:
        PhysicsBody();
        virtual ~PhysicsBody();
        
        virtual PhysicsBodyType body_type() const = 0;
        
        Cookie::Bool dynamic() const;
        void set_dynamic(Cookie::Bool);
        Cookie::Float mass() const;
        void set_mass(Cookie::Float);
        Cookie::Float restitution() const;
        void set_restitution(Cookie::Float);
        Cookie::Node* const node() const;
        void set_node(Cookie::Node* const);
        const Cookie::Vector& velocity() const;
        void set_velocity(Cookie::Vector);
        const Cookie::Vector& acceleration() const;
        void set_acceleration(Cookie::Vector); //?
        
        Cookie::Bool ignores_gravity() const;
        void set_ignores_gravity(Cookie::Bool);
        
    protected:
        Cookie::Bool dynamic_;
        Cookie::Float mass_;
        Cookie::Float restitution_;
        Cookie::Node* node_;
        Cookie::Vector velocity_;
        Cookie::Vector acceleration_;
        Cookie::Bool ignores_gravity_;
    };
}

#endif /* defined(__Cookie__PhysicsBody__) */
