//
//  Keyboard.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Keyboard.h"
#include <SDL2/SDL.h>

Cookie::Keyboard::Keyboard()
{
    
}

void Cookie::Keyboard::process_event(const SDL_Event& e)
{
    if(e.type == SDL_KEYDOWN)
    {
        Cookie::KeyState& keystate = keycode_state_[e.key.keysym.sym];
        keystate.key = e.key.keysym.sym;
        keystate.pressed = true;
        keystate.mod = e.key.keysym.mod;
        
        keystate = scancode_state_[e.key.keysym.scancode];
        keystate.key = e.key.keysym.scancode;
        keystate.pressed = true;
        keystate.mod = e.key.keysym.mod;
        
    }else if(e.type == SDL_KEYUP)
    {
        Cookie::KeyState& keystate = keycode_state_[e.key.keysym.sym];
        keystate.key = e.key.keysym.sym;
        keystate.pressed = false;
        keystate.mod = e.key.keysym.mod;
        
        keystate = scancode_state_[e.key.keysym.scancode];
        keystate.key = e.key.keysym.scancode;
        keystate.pressed = false;
        keystate.mod = e.key.keysym.mod;
    }
}

Cookie::Bool Cookie::Keyboard::isDown(SDL_Keycode key) const
{
    auto keystate = keycode_state_.find(key);
    if(keystate != keycode_state_.end())
    {
        return keystate->second.pressed;
    }else{
        return false;
    }
};

Cookie::Bool Cookie::Keyboard::isDown(SDL_Scancode key) const
{
    auto keystate = scancode_state_.find(key);
    if(keystate != scancode_state_.end())
    {
        return keystate->second.pressed;
    }else{
        return false;
    }
}

Cookie::Bool Cookie::Keyboard::isUp(SDL_Keycode key) const
{
    auto keystate = keycode_state_.find(key);
    if(keystate != keycode_state_.end())
    {
        return !(keystate->second.pressed);
    }else{
        return true;
    }
}

Cookie::Bool Cookie::Keyboard::isUp(SDL_Scancode key) const
{
    auto keystate = scancode_state_.find(key);
    if(keystate != scancode_state_.end())
    {
        return !(keystate->second.pressed);
    }else{
        return true;
    }
}