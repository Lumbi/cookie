//
//  Sound.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Sound.h"

Cookie::Sound::Sound(Cookie::Audio* audio)
{
    audio_ = audio;
}

Cookie::Sound::~Sound()
{
    
}

Cookie::Bool Cookie::Sound::is_playing() const
{
    return is_playing_;
}

void Cookie::Sound::stop()
{
    is_playing_ = false;
    buffer_pos_ = 0;
    loop_ = 0;
}