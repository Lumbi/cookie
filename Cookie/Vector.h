//
//  Vector.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-15.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Vector__
#define __Cookie__Vector__

#include <stdio.h>
#include "Float.h"
#include "Bool.h"

namespace Cookie
{
    typedef struct Vector
    {
        Cookie::Float x;
        Cookie::Float y;
        
        Cookie::Vector& operator+=(const Cookie::Float& rhs);
        Cookie::Vector& operator-=(const Cookie::Float& rhs);
        Cookie::Vector& operator*=(const Cookie::Float& rhs);
        
        Cookie::Vector& operator+=(const Cookie::Vector& rhs);
        Cookie::Vector& operator-=(const Cookie::Vector& rhs);
        
        Cookie::Float length() const;
        Cookie::Float length_squared() const;
        Cookie::Vector unit() const;
        Cookie::Bool is_zero() const;
        
    } Vector;
    
    bool operator==(const Cookie::Vector& lhs, const Cookie::Vector& rhs);
    bool operator!=(const Cookie::Vector& lhs, const Cookie::Vector& rhs);
    Cookie::Vector operator+(const Cookie::Vector& lhs, const Cookie::Vector& rhs);
    Cookie::Vector operator-(const Cookie::Vector& lhs, const Cookie::Vector& rhs);
    Cookie::Vector operator*(const Cookie::Vector& lhs, const Cookie::Float& rhs);
    Cookie::Vector operator*(const Cookie::Float& lhs, const Cookie::Vector& rhs);
}

#endif /* defined(__Cookie__Vector__) */
