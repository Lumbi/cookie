//
//  SDL_Conversion.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__SDL_Conversion__
#define __Cookie__SDL_Conversion__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Rect.h"
#include "Point.h"

namespace Cookie
{
    SDL_Rect convert(const Cookie::Rect&);
    SDL_Point convert(const Cookie::Point&);
}


#endif /* defined(__Cookie__SDL_Conversion__) */
