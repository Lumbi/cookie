//
//  AnimBlock.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__AnimBlock__
#define __Cookie__AnimBlock__

#include <stdio.h>
#include <map>
#include "DrawBlock.h"
#include "Animation.h"

namespace Cookie
{
    /*
     AnimBlock manages multiple animations and renders them to the Renderer.
     AnimBlock will take ownership on added Animation objects.
     */
    class AnimBlock : public Cookie::DrawBlock
    {
    public:
        AnimBlock(Cookie::Renderer*);
        ~AnimBlock();
        
        virtual void update(Cookie::Node& node, Cookie::Game& game);
        
        Cookie::Animation* const anim(Cookie::Int name) const;
        void add_anim(Cookie::Int name, Cookie::Animation*);
        void remove_anim(Cookie::Int name);
        Cookie::Animation* const switch_anim(Cookie::Int name);
        
    private:
        std::map<Cookie::Int, Cookie::Animation*> animations_;
        Cookie::Animation* current_anim_;
    };
}

#endif /* defined(__Cookie__AnimBlock__) */
