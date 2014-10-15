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
#include "World.h"
#include "Renderer.h"

namespace Cookie {
    class Game
    {
    public:
        Game();
        void begin();
        void end();
        void set_fps(Cookie::Float);
        void set_window_size(Cookie::Rect);
        Cookie::Int time_elapsed() const;
        Cookie::Int time_per_frame() const;
    protected:
        void update();
        void render();
    private:
        void loop();
        
    protected:
        Cookie::World world_;
        
    private:
        Cookie::Float fps_;
        Cookie::Int last_frame_tick;
        Cookie::Rect window_size_;
        Cookie::Renderer* renderer_;
        SDL_Window* window_;
        SDL_Surface* surface_;
    };
}

#endif /* defined(__Cookie__Game__) */
