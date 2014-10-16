//
//  DrawBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "DrawBlock.h"

Cookie::DrawBlock::DrawBlock(Renderer* renderer, Sprite* sprite)
{
    renderer_ = renderer;
    sprite_ = sprite;
    draw_point_ = {0.5,0.5};
}

void Cookie::DrawBlock::set_draw_point(Cookie::Point draw_point)
{
    draw_point_ = draw_point;
}

void Cookie::DrawBlock::update(Cookie::Node& node, Cookie::Game& game)
{
    Cookie::Point draw_offset =
    {
        -(draw_point_.x * sprite_->size().w),
        -(draw_point_.y * sprite_->size().h)
    };
    renderer_->addToBatch(*sprite_,
                          draw_offset + node.position(),
                          node.depth());
}