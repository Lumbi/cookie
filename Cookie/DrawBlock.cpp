//
//  DrawBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "DrawBlock.h"

Cookie::DrawBlock::DrawBlock(Renderer* renderer)
{
    renderer_ = renderer;
    draw_point_ = {0.5,0.5};
}

void Cookie::DrawBlock::set_draw_point(Cookie::Point draw_point)
{
    draw_point_ = draw_point;
}