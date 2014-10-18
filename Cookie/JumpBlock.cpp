//
//  JumpBlock.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-17.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "JumpBlock.h"
#include "Game.h"
#include <SDL2/SDL.h>

Cookie::JumpBlock::JumpBlock() : Block()
{
    max_horizontal_acceleration_ = 200;
    horizontal_acceleration_ = 20;
    ground_friction_ = 0.9f;
    initial_jump_acceleration_ = 100;
    is_resting_ = false;
}

void Cookie::JumpBlock::update(Cookie::Node& node, Cookie::Game& game)
{
    static int resting_frame_counter = 0;
    
    if(node.physics_body() != NULL)
    {
        if(fabsf(node.physics_body()->velocity().y) < 2)
        {
            if(!is_resting_)
            {
                ++resting_frame_counter;
                if(resting_frame_counter > 5)
                {
                    is_resting_ = true;
                    resting_frame_counter = 0;
                }
            }

        }else{
            is_resting_ = false;
            resting_frame_counter = 0;
        }
        
        Cookie::Bool move_key_pressed = false;
        
        Cookie::Vector movement_ = {0,0};
        
        if(game.keyboard().isDown(SDLK_RIGHT)){
            movement_.x += horizontal_acceleration_;
            move_key_pressed = true;
        }
        
        if(game.keyboard().isDown(SDLK_LEFT))
        {
            movement_.x -= horizontal_acceleration_;
            move_key_pressed = true;
        }
        
        if(game.keyboard().isDown(SDLK_SPACE))
        {
            if(jump_acceleration_ == 0 && is_resting_)
            {
                jump_acceleration_ = initial_jump_acceleration_;
            }
            jump_acceleration_ *= 0.80f;
        }else{
            jump_acceleration_ = 0;
        }
        
        movement_.y -= jump_acceleration_;
        
        if(node.physics_body()->velocity().x + movement_.x > max_horizontal_acceleration_)
        {
            movement_.x = 0;
        }else if (node.physics_body()->velocity().x + movement_.x < -max_horizontal_acceleration_)
        {
            movement_.x = 0;
        }
        
        Cookie::Vector new_vel = node.physics_body()->velocity();
        new_vel += movement_;
        new_vel.x *= ground_friction_;
        
        node.physics_body()->set_velocity(new_vel);
    }
}