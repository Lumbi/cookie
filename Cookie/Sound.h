//
//  Sound.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Sound__
#define __Cookie__Sound__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include "Bool.h"
#include "Int.h"
#include "Float.h"

namespace Cookie
{
    class Audio;
    
    class Sound
    {
    public:
        Sound(Cookie::Audio* audio);
        virtual ~Sound();
        
        Cookie::Bool open(std::string path);
        
        void play(Cookie::Int repeat = 1);
        void pause();
        void stop();
        
        void set_volume(Cookie::Float volume_);
        void fade_volume(Cookie::Float volume_, Cookie::Int time);
        void fade_volume_then_pause(Cookie::Float volume_, Cookie::Int time);
        void fade_volume_then_stop(Cookie::Float volume_, Cookie::Int time);
        
    private:
        void free();
        
    private:
        Cookie::Audio* audio_;
        Uint8* buffer_;
        Uint32 buffer_lenght_;
        Cookie::Float volume_;
    };
}

#endif /* defined(__Cookie__Sound__) */
