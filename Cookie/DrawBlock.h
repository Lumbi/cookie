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
#include "Point.h"

namespace Cookie
{
    class DrawBlock : public Cookie::Block
    {
    public:
        DrawBlock(Cookie::Renderer*,Cookie::Sprite*);
        virtual const char* name() const {return "DrawBlock"; };
        
        void set_sprite(Cookie::Sprite*) {};
        void set_draw_point(Cookie::Point);
        
        void update(Cookie::Node& node, Cookie::Game& game);
        
    protected:
        Cookie::Renderer* renderer_;
        Cookie::Sprite* sprite_;
        Cookie::Point draw_point_;
    };
}

#endif /* defined(__Cookie__DrawBlock__) */
