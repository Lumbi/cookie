//
//  TextureBlock.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__TextureBlock__
#define __Cookie__TextureBlock__

#include <stdio.h>
#include "DrawBlock.h"
#include "Texture.h"

namespace Cookie
{
    class TextureBlock : public Cookie::DrawBlock
    {
    public:
        TextureBlock(Cookie::Renderer*, Cookie::Texture*);
        virtual ~TextureBlock();
        
        virtual void update(Cookie::Node& node, Cookie::Game& game);
        
    protected:
        Cookie::Texture* texture_;
    };
}

#endif /* defined(__Cookie__TextureBlock__) */
