//
//  Rotation.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Rotation.h"
#include <cmath>

Cookie::Float Cookie::wrap_degrees(Cookie::Float degrees)
{
    if(degrees >= 360)
    {
        float intpart;
        float fracpart = modff(degrees, &intpart);
        degrees = ((int)intpart % 360) + fracpart;
    }
    return degrees;
}