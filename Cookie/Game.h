//
//  Game.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Game__
#define __Cookie__Game__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Float.h"
#include "Rect.h"
#include "Physics.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "Audio.h"
#include "World.h"

namespace Cookie
{
    class Game
    {
    public:
        Game();
        void begin();
        void end();
        void set_fps(Cookie::Float);
        void set_window_size(Cookie::Rect);
        Cookie::World* const world() const;
        Cookie::Int time_elapsed() const;
        Cookie::Int time_per_frame() const;
        const Cookie::Keyboard& keyboard() const;
    private:
        void update();
        void render();
        void loop();
        
    protected:
        Cookie::World* world_;
        
    private:
        Cookie::Float fps_;
        Cookie::Int last_frame_tick;
        Cookie::Rect window_size_;
        Cookie::Renderer* renderer_;
        Cookie::Audio* audio_;
        Cookie::Keyboard keyboard_;
        
        SDL_Window* window_;
        SDL_Surface* surface_;
        SDL_GLContext gl_context_;
        SDL_TimerID main_loop_timer_;
    };
}

#endif /* defined(__Cookie__Game__) */
