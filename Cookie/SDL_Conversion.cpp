//
//  SDL_Conversion.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "SDL_Conversion.h"
#include <cmath>

SDL_Rect Cookie::convert(const Cookie::Rect& rect)
{
    return
    {
        (int)round(rect.x),
        (int)round(rect.y),
        (int)round(rect.w),
        (int)round(rect.h)
    };
}