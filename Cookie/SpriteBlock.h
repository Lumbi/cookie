//
//  SpriteBlock.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__SpriteBlock__
#define __Cookie__SpriteBlock__

#include <stdio.h>
#include "DrawBlock.h"

namespace Cookie
{
    class SpriteBlock : public Cookie::DrawBlock
    {
    public:
        SpriteBlock(Cookie::Renderer*, Cookie::Sprite*);

        void set_color(Cookie::Color);
        
        virtual void update(Cookie::Node& node, Cookie::Game& game);
        
    protected:
        Cookie::Sprite* sprite_;
        Cookie::Color color_;
    };
}

#endif /* defined(__Cookie__SpriteBlock__) */
