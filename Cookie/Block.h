//
//  Block.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Block__
#define __Cookie__Block__

#include <stdio.h>
#include "Bool.h"

namespace Cookie
{
    class Node;
    class Game;
    
    class Block
    {
    public:
        virtual void update(const Cookie::Node& node, const Cookie::Game& game) = 0;
        virtual const char* name() const {return ""; };
        
        virtual Cookie::Bool active() const {return true; };
        virtual void set_activate(Cookie::Bool) {};
        
    protected:
        Cookie::Bool active_;
    };
    
    bool operator==(const Cookie::Block& lhs, const Cookie::Block& rhs);
}

#endif /* defined(__Cookie__Block__) */
