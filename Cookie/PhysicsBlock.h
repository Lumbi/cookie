//
//  PhysicsBlock.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__PhysicsBlock__
#define __Cookie__PhysicsBlock__

#include <stdio.h>
#include "Block.h"
#include "Vector.h"
#include "Physics.h"

namespace Cookie
{
    class PhysicsBlock : public Cookie::Block
    {
    public:
        PhysicsBlock(const Physics*);
        
        virtual void update(Cookie::Node& node, Cookie::Game& game);
        
        virtual const char* name() const {return "PhysicsBlock"; };
        
        const Cookie::Vector& velocity() const;
        void set_velocity(Cookie::Vector);
        
    private:
        Cookie::Vector velocity_;
        
    private:
        const Physics * physics_;
    };
    
}

#endif /* defined(__Cookie__PhysicsBlock__) */
