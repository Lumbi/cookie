//
//  Camera.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-16.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Camera.h"

Cookie::Camera::Camera() : Cookie::Node()
{
}

void Cookie::Camera::set_viewport(Cookie::Rect viewport)
{
    viewport_ = viewport;
}

const Cookie::Rect& Cookie::Camera::viewport() const
{
    return viewport_;
}