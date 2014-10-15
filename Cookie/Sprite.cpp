//
//  Sprite.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-14.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Sprite.h"

Cookie::Sprite::Sprite(SDL_Surface* surface)
{
    sdl_surface_ = surface;
}

SDL_Surface* Cookie::Sprite::sdl_surface() const
{
    return sdl_surface_;
}

Cookie::Rect Cookie::Sprite::size() const
{
    return { 0, 0, static_cast<Float>(sdl_surface_->w), static_cast<Float>(sdl_surface_->h) };
}