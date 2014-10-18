//
//  RectBody.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "RectBody.h"

Cookie::RectBody::RectBody() : PhysicsBody()
{
    rectangle_ = {0,0,1,1};
}

Cookie::RectBody::~RectBody()
{
}

Cookie::Rect Cookie::RectBody::rectangle() const
{
    return rectangle_;
}

void Cookie::RectBody::set_rectangle(Cookie::Rect rectangle)
{
    rectangle_ = rectangle;
}