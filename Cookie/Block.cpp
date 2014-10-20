//
//  Block.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Block.h"

Cookie::Block::Block()
{
    active_ = true;
}

Cookie::Block::~Block()
{
    
}

bool Cookie::operator==(const Cookie::Block& lhs, const Cookie::Block& rhs)
{
    return &lhs == &rhs;
};