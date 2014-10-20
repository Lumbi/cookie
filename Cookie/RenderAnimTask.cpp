//
//  RenderAnimTask.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "RenderAnimTask.h"

Cookie::RenderAnimTask::RenderAnimTask(Cookie::Renderer* renderer, Cookie::Animation* animation)
: Cookie::RenderTask(renderer)
{
    animation_ = animation;
}

Cookie::RenderAnimTask::~RenderAnimTask()
{
}

void Cookie::RenderAnimTask::render(Cookie::Point origin) const
{
    animation_->render(renderer_, origin + position);
}