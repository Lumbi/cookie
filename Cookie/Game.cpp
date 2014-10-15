//
//  Game.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Game.h"
#include <SDL2/SDL.h>
#include "DrawBlock.h"

Cookie::Game::Game()
{
    fps_ = 30;
    window_size_ = {0,0,800, 600};
    window_ = NULL;
    surface_ = NULL;
    world_ = Cookie::World();
    renderer_ = NULL;
}

void Cookie::Game::set_fps(Cookie::Float fps)
{
    fps_ = fps;
}

void Cookie::Game::set_window_size(Cookie::Rect size)
{
    window_size_ = size;
}

void Cookie::Game::begin()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        printf("Could not initialize game.\n");
        return;
    }
    
    window_ = SDL_CreateWindow("Title",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               window_size_.w, window_size_.h,
                               SDL_WINDOWPOS_CENTERED |
                               SDL_WINDOW_SHOWN |
                               SDL_WINDOW_OPENGL);
    if (window_ == NULL)
    {
        printf("Could not create game window.\n");
        return;
    }
    
    surface_ = SDL_GetWindowSurface(window_);
    
    if(surface_ == NULL)
    {
        printf("Could not grab window's surface.\n");
        return;
    }
    
    renderer_ = new Renderer(surface_);
    
    
#pragma TEST
    Node* test = new Node();
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0,0,0,0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    Sprite* sprite = new Sprite(surface);
    DrawBlock* block = new DrawBlock(renderer_, sprite);
    test->add_block(block);
    world_.add_child(test);
#pragma TEST
    
    loop();
    
    end();
}

void Cookie::Game::loop()
{
    Cookie::Int t_elapsed;
    Cookie::Int t_per_frame;
    while (1) {
        last_frame_tick = SDL_GetTicks();
        update();
        render();
        t_elapsed = time_elapsed();
        t_per_frame = time_per_frame();
        if(t_elapsed < t_per_frame)
        {
            SDL_Delay(t_per_frame-t_elapsed);
        }
    }
}

Cookie::Int Cookie::Game::time_elapsed() const
{
    return SDL_GetTicks() - last_frame_tick;
}

Cookie::Int Cookie::Game::time_per_frame() const
{
    return 1/fps_ * 1000;
}

void Cookie::Game::end()
{
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void recursive_update(Cookie::Node& node, Cookie::Game& game)
{
    for(auto block = node.blocks_begin(); block != node.blocks_end(); ++block)
    {
        (*block)->update(node, game);
    }
    
    for(auto child = node.children_begin(); child != node.children_end(); ++child)
    {
        recursive_update(**child, game);
    }
}

void Cookie::Game::update()
{
    recursive_update(world_, *this);
}

void Cookie::Game::render()
{
    renderer_->renderBatch();
    SDL_UpdateWindowSurface(window_);
}