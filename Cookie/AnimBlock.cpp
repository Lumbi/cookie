//
//  AnimBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AnimBlock.h"

Cookie::AnimBlock::AnimBlock(Cookie::Renderer* renderer) : Cookie::DrawBlock(renderer)
{
    current_anim_ = NULL;
}

Cookie::AnimBlock::~AnimBlock()
{
    for (auto it = animations_.begin(); it != animations_.end(); ++it) {
        delete (*it).second;
    }
    animations_.clear();
}

void Cookie::AnimBlock::update(Cookie::Node& node, Cookie::Game& game)
{
    if(current_anim_ != NULL)
    {
        current_anim_->update(game.time_elapsed());
        
        Cookie::Point draw_offset =
        {
            -(draw_point_.x * current_anim_->frame().w),
            -(draw_point_.y * current_anim_->frame().h)
        };
        renderer_->addToBatch(*current_anim_, draw_offset + node.position_world());
    }
}

Cookie::Animation* const Cookie::AnimBlock::anim(Cookie::Int name) const
{
    auto found = animations_.find(name);
    if(found != animations_.end())
    {
        return (*found).second;
    }else{
        return NULL;
    }
}

void Cookie::AnimBlock::add_anim(Cookie::Int name, Cookie::Animation* anim)
{
    auto found = animations_.find(name);
    if(found != animations_.end())
    {
        delete (*found).second;
    }
    animations_[name] = anim;
    if(current_anim_ == NULL)
    {
        current_anim_ = anim;
    }
}

void Cookie::AnimBlock::remove_anim(Cookie::Int name)
{
    auto found = animations_.find(name);
    if(found != animations_.end())
    {
        delete (*found).second;
        animations_.erase(found);
    }
}

Cookie::Animation* const Cookie::AnimBlock::switch_anim(Cookie::Int name)
{
    auto found = animations_.find(name);
    if(found != animations_.end())
    {
        current_anim_ = (*found).second;
        return current_anim_;
    }else{
        return NULL;
    }
}