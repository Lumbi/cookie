//
//  JumpBlock.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__JumpBlock__
#define __Cookie__JumpBlock__

#include <stdio.h>
#include "Block.h"
#include "Vector.h"

namespace Cookie
{
    class JumpBlock : public Block
    {
    public:
        JumpBlock();
        virtual const char* name() const {return "JumpBlock"; };
        
        virtual void update(Cookie::Node& node, Cookie::Game& game);
        
    private:
        Cookie::Float horizontal_acceleration_;
        Cookie::Float max_horizontal_acceleration_;
        Cookie::Float ground_friction_;
        Cookie::Float initial_jump_acceleration_;
        Cookie::Float jump_acceleration_;
        Cookie::Bool is_resting_;
    };
}

#endif /* defined(__Cookie__JumpBlock__) */
