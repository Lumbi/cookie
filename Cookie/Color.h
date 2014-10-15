//
//  Color.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Color__
#define __Cookie__Color__

#include <stdio.h>
#include "Float.h"

namespace Cookie
{
    typedef struct Color
    {
        Cookie::Float r;
        Cookie::Float g;
        Cookie::Float b;
        Cookie::Float a;
    } Color;
    
    const Cookie::Color kColorBlack = {0,0,0,1};
    const Cookie::Color kColorWhite = {1,1,1,1};
    const Cookie::Color kColorGray = {0.5,0.5,0.5,1};
}

#endif /* defined(__Cookie__Color__) */
