//
//  Camera.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-16.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Camera__
#define __Cookie__Camera__

#include <stdio.h>
#include "Node.h"
#include "Rect.h"

namespace Cookie
{
    class Camera : public Node
    {
    public:
        Camera();
        const Cookie::Rect& viewport() const;
        void set_viewport(Cookie::Rect);
    private:
        Cookie::Rect viewport_;
    };
}

#endif /* defined(__Cookie__Camera__) */
