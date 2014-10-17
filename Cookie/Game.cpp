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
#include "SpriteBlock.h"
#include "PhysicsBlock.h"
#include <SDL2/SDL_opengl.h>

Cookie::Bool initGL();

Cookie::Game::Game()
{
    fps_ = 60;
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
    if (SDL_Init(SDL_INIT_EVERYTHING))
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
    
    gl_context_ = SDL_GL_CreateContext(window_);
    
    if(!initGL())
    {
        printf("Could not init OpenGL\n");
        return;
    }
    
    surface_ = SDL_GetWindowSurface(window_);
    
    if(surface_ == NULL)
    {
        printf("Could not grab window's surface.\n");
        return;
    }
    
    renderer_ = new Renderer(surface_);
    renderer_->set_camera(world_.camera());
    world_.camera()->set_viewport({0,0,window_size_.w, window_size_.h});
    
#pragma TEST
    Node* test = new Node();
    test->translate_by(0, -200);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0,0,0,0);
    
    Sprite* sprite = new Sprite(surface);
    SpriteBlock* draw_block = new SpriteBlock(renderer_, sprite);
    draw_block->set_color({ 1,0,1,1 });
    test->add_block(draw_block);
    
    PhysicsBlock* phys_block = new PhysicsBlock(&(world_.physics()));
    test->add_block(phys_block);
    world_.add_child(test);
#pragma TEST
    
    loop();
    end();
}

Cookie::Bool initGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL\n");
        return false;
    }
    return true;
}

void Cookie::Game::loop()
{
    static Cookie::Int t_per_frame;
    static Cookie::Int t_loop;
    
    while (1)
    {
        t_loop = SDL_GetTicks();
        update();
        last_frame_tick = SDL_GetTicks();
        render();
        t_loop = SDL_GetTicks() - t_loop;
        t_per_frame = time_per_frame();
        if(t_loop < t_per_frame)
        {
            SDL_Delay(t_per_frame-t_loop);
        }
    }
}

Cookie::Int Cookie::Game::time_elapsed() const
{
    return (SDL_GetTicks() - last_frame_tick);
}

Cookie::Int Cookie::Game::time_per_frame() const
{
    return 1/fps_ * 1000;
}

void Cookie::Game::end()
{
    SDL_RemoveTimer(main_loop_timer_);
    SDL_GL_DeleteContext(gl_context_);
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
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    renderer_->renderBatch();
    SDL_GL_SwapWindow(window_);
}