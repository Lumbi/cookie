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
#include "JumpBlock.h"
#include <SDL2/SDL_opengl.h>
#include "RectBody.h"

Cookie::Bool initGL();

Cookie::Game::Game()
{
    fps_ = 60;
    window_size_ = {0,0,800, 600};
    window_ = NULL;
    surface_ = NULL;
    world_ = new Cookie::World();
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

const Cookie::Keyboard& Cookie::Game::keyboard() const
{
    return keyboard_;
}

Cookie::World* const Cookie::Game::world() const
{
    return world_;
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
    renderer_->set_camera(world_->camera());
    world_->camera()->set_viewport({0,0,window_size_.w, window_size_.h});
    
#pragma TEST
    Node* test = new Node();
    test->translate_by(0, -200);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0,0,0,0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    
    Sprite* sprite = new Sprite(surface);
    SpriteBlock* draw_block = new SpriteBlock(renderer_, sprite);
    draw_block->set_color({ 1,0,1,1 });
    test->add_block(draw_block);
    
    JumpBlock* mov_block = new JumpBlock();
    test->add_block(mov_block);
    
    RectBody* rect_body = new RectBody();
    rect_body->set_rectangle(sprite->size());
    rect_body->set_dynamic(true);
    rect_body->set_mass(10);
    rect_body->set_restitution(0);
    test->set_physics_body(rect_body);
    
    Node* platform = new Node();
    platform->translate_by(0, 200);
    SDL_Surface* plat_surface = SDL_CreateRGBSurface(0, 400, 50, 32, 0,0,0,0);
    SDL_FillRect(plat_surface, NULL, SDL_MapRGB(plat_surface->format, 0, 255, 0));
    
    Sprite* plat_sprite = new Sprite(plat_surface);
    SpriteBlock* plat_draw_block = new SpriteBlock(renderer_, plat_sprite);
    plat_draw_block->set_color({0,1,1,1});
    platform->add_block(plat_draw_block);
    
    RectBody* plat_body = new RectBody();
    plat_body->set_rectangle(plat_sprite->size());
    plat_body->set_mass(100);
    platform->set_physics_body(plat_body);
    
    world_->add_child(test);
    world_->add_child(platform);
    
    world_->set_name(std::string("World"));
    test->set_name(std::string("test"));
    platform->set_name(std::string("platform"));
#pragma TEST
    
    loop();
    end();
}

Cookie::Bool initGL()
{
    glDisable(GL_DEPTH_TEST);
    
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
    last_frame_tick = SDL_GetTicks();
    
    while (1)
    {
        t_loop = SDL_GetTicks();
        
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            keyboard_.process_event(e);
        }
        
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
    recursive_update(*world_, *this);
    world_->physics()->update(*this);
}

void Cookie::Game::render()
{
//    glClearColor(0, 0, 0, 1);
//    glClear(GL_COLOR_BUFFER_BIT);
    
    SDL_FillRect( surface_, NULL, SDL_MapRGB( surface_->format, 0, 0, 0 ) );
    
    renderer_->renderBatch();
    
    SDL_UpdateWindowSurface(window_);
//    SDL_GL_SwapWindow(window_);
}