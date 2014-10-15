//
//  Rotation.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Rotation__
#define __Cookie__Rotation__

#include <stdio.h>
#include "Float.h"

namespace Cookie
{
    Cookie::Float wrap_degrees(Cookie::Float degrees);
    
    const Cookie::Float kHalfCircle = 180;
    const Cookie::Float kQuarterCircle = 90;
}

#endif /* defined(__Cookie__Rotation__) */
