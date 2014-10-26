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
#include "Audio.h"

namespace Cookie
{
    class Sound
    {
        friend class Audio;
    public:
        Sound(Cookie::Audio* audio);
        virtual ~Sound();
        
        Cookie::Bool open(std::string path);
        
        void play(Cookie::Int loop = 1);
        void pause();
        void stop();
        
        Cookie::Bool is_playing() const;
        
        void set_volume(Cookie::Float volume_);
        void fade_volume(Cookie::Float volume_, Cookie::Int time);
        void fade_volume_then_pause(Cookie::Float volume_, Cookie::Int time);
        void fade_volume_then_stop(Cookie::Float volume_, Cookie::Int time);
        
    private:
        void free();
        friend int audio_queue_thread_func (void *);
        
    private:
        Cookie::Audio* audio_;
        Cookie::Bool is_playing_;
        Cookie::Int channel_;
        Uint8* buffer_;
        Uint32 buffer_length_;
        Uint32 buffer_pos_;
        Cookie::Int loop_;
        Cookie::Float volume_;
    };
}

#endif /* defined(__Cookie__Sound__) */
