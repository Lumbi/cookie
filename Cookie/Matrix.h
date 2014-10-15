//
//  Matrix.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Matrix__
#define __Cookie__Matrix__

#include <stdio.h>
#include <glm/detail/type_mat3x3.hpp>
#include "glm.hpp"
#include "Point.h"
#include "Rect.h"
#include "Float.h"

#define __COOKIE_MATRIX_TYPE__ float
#define __COOKIE_MATRIX_PRECISION__ glm::mediump

namespace Cookie
{
    typedef glm::detail::tmat3x3<__COOKIE_MATRIX_TYPE__, __COOKIE_MATRIX_PRECISION__> Matrix;
    
    Cookie::Matrix matrix_make_zero();
    Cookie::Matrix matrix_make(Cookie::Float m11, Cookie::Float m12, Cookie::Float m13,
                               Cookie::Float m21, Cookie::Float m22, Cookie::Float m23,
                               Cookie::Float m31, Cookie::Float m32, Cookie::Float m33);
    Cookie::Matrix matrix_translate(const Cookie::Matrix&, Cookie::Float dx, Cookie::Float dy);
    Cookie::Matrix matrix_rotate(const Cookie::Matrix&, Cookie::Float degrees);
    Cookie::Point matrix_transform_point(const Cookie::Matrix&, Cookie::Point);
    Cookie::Rect matrix_transform_rect(const Cookie::Matrix&, Cookie::Rect);
}

#endif /* defined(__Cookie__Matrix__) */
