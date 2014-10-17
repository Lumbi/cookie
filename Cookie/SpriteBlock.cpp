//
//  SpriteBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "SpriteBlock.h"

Cookie::SpriteBlock::SpriteBlock(Renderer* renderer, Sprite* sprite) : Cookie::DrawBlock(renderer)
{
    sprite_ = sprite;
}

void Cookie::SpriteBlock::set_color(Cookie::Color color)
{
    color_ = color;
}

void Cookie::SpriteBlock::update(Cookie::Node& node, Cookie::Game& game)
{
    Cookie::Point draw_offset =
    {
        -(draw_point_.x * sprite_->size().w),
        -(draw_point_.y * sprite_->size().h)
    };

    Cookie::Rect dst = sprite_->size() + draw_offset + node.position();
    renderer_->addToBatch(dst, color_, node.depth());
    
    //TODO:
//    renderer_->addToBatch(*sprite_,
//                          draw_offset + node.position(),
//                          node.depth());
}