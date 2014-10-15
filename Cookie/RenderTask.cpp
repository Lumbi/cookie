//
//  RenderTask.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "RenderTask.h"

bool Cookie::operator<(const Cookie::RenderTask& lhs, const Cookie::RenderTask& rhs)
{
    return lhs.depth > rhs.depth;
}