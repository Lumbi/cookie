//
//  RectRenderTask.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "RectRenderTask.h"
#include <SDL2/SDL_opengl.h>

Cookie::RectRenderTask::~RectRenderTask()
{
    
}

void Cookie::RectRenderTask::render(Cookie::Point origin) const
{
    //TODO: blit surface
    glColor4f(color.r, color.g, color.b, color.a);
    glRectf(origin.x+rect.x, origin.y+rect.y, origin.x+rect.x+rect.w, origin.y+rect.y+rect.h);
}