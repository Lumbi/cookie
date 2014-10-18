//
//  RectBody.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__RectBody__
#define __Cookie__RectBody__

#include <stdio.h>
#include "PhysicsBody.h"
#include "Rect.h"

namespace Cookie
{
    class RectBody : public PhysicsBody
    {
    public:
        RectBody();
        virtual ~RectBody();
        PhysicsBodyType body_type() const {return RectangleBodyType; };
        
        Cookie::Rect rectangle() const;
        void set_rectangle(Cookie::Rect);
        
    private:
        Cookie::Rect rectangle_;
    };
}

#endif /* defined(__Cookie__RectBody__) */
