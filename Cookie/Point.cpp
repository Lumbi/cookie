//
//  Point.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Point.h"
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

Cookie::Point Cookie::Point::rotate_by(Cookie::Float degrees) const
{
    auto rot = glm::rotate(glm::mat3x3(),degrees);
    auto result = rot * glm::vec3(x,y,1);
    return { result[0] , result[1] };
}

Cookie::Point Cookie::Point::rotate_to(Cookie::Float degrees) const
{
    float angle = glm::degrees(glm::atan(y, x));
    return rotate_by(degrees-angle);
}

Cookie::Point& Cookie::Point::operator+=(const Cookie::Point& rhs)
{
    x+=rhs.x;
    y+=rhs.y;
    return *this;
}

Cookie::Point& Cookie::Point::operator-=(const Cookie::Point& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
    return *this;
}

Cookie::Point Cookie::operator+(Cookie::Point lhs, const Cookie::Point& rhs)
{
    return { lhs.x+rhs.x , lhs.y+rhs.y };
}

Cookie::Point Cookie::operator-(Cookie::Point lhs, const Cookie::Point& rhs)
{
    return { lhs.x-rhs.x , lhs.y-rhs.y };
}