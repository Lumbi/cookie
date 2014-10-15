//
//  Matrix.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Matrix.h"
#include "glm/detail/type_mat3x3.hpp"
#include "glm/gtx/transform2.hpp"

Cookie::Matrix Cookie::matrix_make_zero(){
    return glm::mat3x3::tmat3x3<__COOKIE_MATRIX_TYPE__, __COOKIE_MATRIX_PRECISION__>();
}

Cookie::Matrix Cookie::matrix_translate(const Matrix & m, Cookie::Float dx, Cookie::Float dy)
{
    auto translation = glm::mat3x3::tmat3x3<__COOKIE_MATRIX_TYPE__, __COOKIE_MATRIX_PRECISION__>
    (
     0, 0, dx,
     0, 0, dy,
     0, 0, 1
     );
    return translation * m;
}

Cookie::Matrix Cookie::matrix_rotate(const Matrix & m, Cookie::Float degrees)
{
    float radians = glm::radians<float>(degrees);
    float cos = glm::cos<float>(radians);
    float sin = glm::sin<float>(radians);
    auto rotation = glm::mat3x3::tmat3x3<float, __COOKIE_MATRIX_PRECISION__>
    (
     cos, -sin, 0,
     sin, cos, 0,
     0, 0, 1
     );
    return rotation * m;
}

Cookie::Point Cookie::matrix_transform_point(const Cookie::Matrix& m, Cookie::Point p)
{
    Cookie::Point result;
    result.x = m[0][0]*p.x + m[1][0]*p.y;
    result.y = m[0][1]*p.y + m[1][1]*p.y;
    return result;
}