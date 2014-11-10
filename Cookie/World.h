//
//  World.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__World__
#define __Cookie__World__

#include <stdio.h>
#include "Node.h"
#include "Camera.h"

namespace Cookie
{
    class Physics;
    
    class World : public Node
    {
    public:
        World();
        Cookie::Physics* const physics() const;
        Cookie::Camera* camera() const;
    private:
        Cookie::Physics* physics_;
        Cookie::Camera* camera_;
    };
}

#endif /* defined(__Cookie__World__) */
