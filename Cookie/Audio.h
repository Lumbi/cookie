//
//  Audio.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Audio__
#define __Cookie__Audio__

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>

namespace Cookie
{
    static const Uint32 kAudioBufferLength = 32768;
    
    class Sound;
    class Audio
    {
    public:
        Audio();
        virtual ~Audio();
        
        void init();
        
        void queue(Cookie::Sound*);
        
    private:
        friend int audio_queue_thread_func (void *);
        
    private:
        std::vector<Cookie::Sound*> sound_queue_;

    };
}

#endif /* defined(__Cookie__Audio__) */
