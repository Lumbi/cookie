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
 
    class AudioPipeline;
    class Sound;
    class Audio
    {
    public:
        Audio();
        virtual ~Audio();
        
        void init();
        
        void queue(Cookie::Sound*);
        SDL_AudioSpec get_audio_spec() const;
        
    private:
        friend int audio_queue_thread_func (void *);
        friend void audio_pipeline_callback(const Uint8* const data, Uint32 len, void* userdata);
        
    private:
        Cookie::AudioPipeline* audio_pipeline_;
        SDL_AudioSpec device_audio_spec_;
        std::vector<Cookie::Sound*> sound_queue_;
        SDL_AudioDeviceID device_;
    };
}

#endif /* defined(__Cookie__Audio__) */
