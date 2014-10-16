//
//  DrawBlock.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__DrawBlock__
#define __Cookie__DrawBlock__

#include <stdio.h>
#include "Game.h"
#include "Renderer.h"
#include "Sprite.h"

namespace Cookie
{
    class DrawBlock : public Block
    {
    public:
        DrawBlock(Renderer*,Sprite*);
        virtual const char* name() const {return "DrawBlock"; };
        
        void set_sprite(Sprite*) {};
        
        void update(Cookie::Node& node, Cookie::Game& game);
        
    protected:
        Renderer* renderer_;
        Sprite* sprite_;
    };
}

#endif /* defined(__Cookie__DrawBlock__) */
