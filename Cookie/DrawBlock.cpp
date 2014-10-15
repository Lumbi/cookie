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
}

void Cookie::DrawBlock::update(const Cookie::Node& node, const Cookie::Game& game)
{
    renderer_->addToBatch(*sprite_, node.position(), node.depth());
}