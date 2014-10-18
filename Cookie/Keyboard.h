//
//  Keyboard.h
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#ifndef __Cookie__Keyboard__
#define __Cookie__Keyboard__

#include <stdio.h>
#include <SDL2/SDL.h>
#include "InputMethod.h"
#include "Bool.h"
#include "Int.h"
#include <map>

namespace Cookie
{
    typedef struct
    {
        Cookie::Int key;
        Cookie::Bool pressed;
        Cookie::Int mod;
    } KeyState;
    
    class Keyboard
    {
    public:
        Keyboard();
        void process_event(const SDL_Event&);
        Cookie::Bool isDown(SDL_Keycode) const;
        Cookie::Bool isDown(SDL_Scancode) const;
        Cookie::Bool isUp(SDL_Keycode) const;
        Cookie::Bool isUp(SDL_Scancode) const;
        
        //TODO:
//        Cookie::Bool isDown(SDL_Keymod, SDL_Keycode) const;
//        Cookie::Bool isDown(SDL_Keymod, SDL_Scancode) const;
//        Cookie::Bool isUp(SDL_Keymod, SDL_Keycode) const;
//        Cookie::Bool isUp(SDL_Keymod, SDL_Scancode) const;
        
    private:
        std::map<SDL_Keycode, KeyState> keycode_state_;
        std::map<SDL_Scancode, KeyState> scancode_state_;
    };
}

#endif /* defined(__Cookie__Keyboard__) */
