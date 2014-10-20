//
//  Animation.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Animation__
#define __Cookie__Animation__

#include <stdio.h>
#include "Texture.h"

namespace Cookie
{
    typedef enum
    {
        NO_LOOP,
        NO_LOOP_REVERSE,
        LOOP_FORWARD,
        LOOP_REVERSE,
        LOOP_PING_PONG
    } AnimationLoop;
    
    class Animation
    {
    public:
        Animation(Cookie::Texture*,
                  Cookie::Int frame_count = 0,
                  const Cookie::Rect* frame = NULL,
                  Cookie::Int start_frame = 0);
        
        virtual ~Animation();
        
        virtual void update(Cookie::Int time_elapsed);
        virtual void play();
        virtual void pause();
        virtual void reset();
        virtual void render(Cookie::Renderer* renderer,
                            Cookie::Point pos,
                            Cookie::TextureRenderFlip flip = NO_FLIP,
                            Cookie::Float angle = 0,
                            const Cookie::Point* center = NULL);
        
        const Cookie::Int& name() const;
        void set_name(Cookie::Int name);
        
        Cookie::Int current_frame() const;
        
        const Cookie::Bool& is_playing() const;
        
        const Cookie::Rect& frame() const;
        
        Cookie::Int frame_count() const;
        
        void set_fps(Cookie::Int);
        
        void set_loop(Cookie::AnimationLoop);
        
    protected:
        Cookie::Texture* sheet_;
        Cookie::Int name_;
        Cookie::Int current_frame_;
        Cookie::Int start_frame_;
        Cookie::Int frame_count_;
        Cookie::Rect frame_;
        Cookie::Int fps_;
        Cookie::AnimationLoop loop_;
        Cookie::Bool playing_;
    };
}

#endif /* defined(__Cookie__Animation__) */
