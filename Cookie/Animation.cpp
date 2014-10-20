//
//  Animation.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Animation.h"

inline Cookie::Int time_per_frame(Cookie::Int fps);

#pragma mark - Constructors & Destructors

Cookie::Animation::Animation(Cookie::Texture* sheet,
                             Cookie::Int frame_count,
                             const Cookie::Rect* frame,
                             Cookie::Int start_frame)
{
    sheet_ = sheet;
    name_ = 0;
    frame_count_ = frame_count;
    
    if(frame != NULL)
    {
        frame_ = *frame;
    }else{
        frame_ = {0,0,sheet_->width()/frame_count_,sheet_->height()};
    }
    start_frame_ = start_frame;
    fps_ = 1;
    playing_ = false;
    current_frame_ = 0;
}

Cookie::Animation::~Animation()
{
    sheet_ = NULL;
}

#pragma Instance Methods

void Cookie::Animation::update(Cookie::Int time_elapsed)
{
    static Cookie::Int time_since_last_frame = 0;
    static Cookie::Int direction = -1;
    time_since_last_frame += time_elapsed;
    
    if(playing_ && time_since_last_frame >= time_per_frame(fps_))
    {
        switch (loop_) {
            case NO_LOOP:
                if(current_frame_ < frame_count_-1)
                {
                    ++current_frame_;
                }else{
                    current_frame_ = frame_count_-1;
                    playing_ = false;
                }
                break;
            case NO_LOOP_REVERSE:
                if(current_frame_ > 0)
                {
                    --current_frame_;
                }else{
                    current_frame_ = 0;
                    playing_ = false;
                }
                break;
            case LOOP_FORWARD:
                if(current_frame_ < frame_count_-1)
                {
                    ++current_frame_;
                }else{
                    current_frame_ = 0;
                }
                break;
            case LOOP_REVERSE:
                if(current_frame_ > 0)
                {
                    --current_frame_;
                }else{
                    current_frame_ = frame_count_ - 1;
                }
                break;
            case LOOP_PING_PONG:
                if(current_frame_ == 0 || current_frame_ == frame_count_-1)
                {
                    direction *= -1;
                }
                current_frame_ += direction;
                break;
        }
    }
}

void Cookie::Animation::play()
{
    playing_ = true;
}

void Cookie::Animation::pause()
{
    playing_ = false;
}

void Cookie::Animation::reset()
{
    if(loop_ != NO_LOOP_REVERSE && loop_ != LOOP_REVERSE)
    {
        current_frame_ = 0;
    }else{
        current_frame_ = frame_count_ - 1;
    }
}

void Cookie::Animation::render(Cookie::Renderer* renderer,
                               Cookie::Point pos,
                               Cookie::TextureRenderFlip flip,
                               Cookie::Float angle,
                               const Cookie::Point* center)
{
    
}

#pragma mark - Accessors & Mutators

const Cookie::Int& Cookie::Animation::name() const
{
    return name_;
}

void Cookie::Animation::set_name(Cookie::Int name)
{
    name_ = name;
}

Cookie::Int Cookie::Animation::current_frame() const
{
    return current_frame_;
}

const Cookie::Bool& Cookie::Animation::is_playing() const
{
    return playing_;
}

const Cookie::Rect& Cookie::Animation::frame() const
{
    return frame_;
}

Cookie::Int Cookie::Animation::frame_count() const
{
    return frame_count_;
}

void Cookie::Animation::set_fps(Cookie::Int fps)
{
    fps_ = fps;
}

void Cookie::Animation::set_loop(Cookie::AnimationLoop loop)
{
    loop_ = loop;
}

#pragma mark - Utility

Cookie::Int time_per_frame(Cookie::Int fps)
{
    return (1/fps * 1000);
}
