//
//  TextureBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-19.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "TextureBlock.h"

Cookie::TextureBlock::TextureBlock(Renderer* renderer, Cookie::Texture* texture) : Cookie::DrawBlock(renderer)
{
    texture_ = texture;
}

void Cookie::TextureBlock::update(Cookie::Node& node, Cookie::Game& game)
{
    Cookie::Point draw_offset =
    {
        -(draw_point_.x * texture_->width()),
        -(draw_point_.y * texture_->height())
    };
    renderer_->addToBatch(*texture_,
                          draw_offset + node.position(),
                          node.depth());
}