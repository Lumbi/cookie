//
//  Game.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-12.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Game.h"
#include <SDL2/SDL.h>
#include <string>
#include "DrawBlock.h"
#include "TextureBlock.h"
#include "JumpBlock.h"
#include "RectBody.h"
#include "Texture.h"
#include "Animation.h"

Cookie::Game::Game()
{
#warning BUG higher FPS increases game speed
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
                               SDL_WINDOW_SHOWN);
    
    if (window_ == NULL)
    {
        printf("Could not create game window: %s\n",SDL_GetError());
        return;
    }
    
    surface_ = SDL_GetWindowSurface(window_);
    
    if(surface_ == NULL)
    {
        printf("Could not grab window's surface: %s\n",SDL_GetError());
        return;
    }
    
    renderer_ = new Renderer(window_);
    renderer_->set_camera(world_->camera());
    world_->camera()->set_viewport({0,0,window_size_.w, window_size_.h});
    
#pragma mark - TEST
    Node* test = new Node();
    test->translate_by(0, -200);
    
    Texture* texture = new Texture();
    texture->open(std::string("block.bmp"), renderer_);
    
    TextureBlock* draw_block = new TextureBlock(renderer_, texture);
    test->add_block(draw_block);
    
    JumpBlock* mov_block = new JumpBlock();
    test->add_block(mov_block);
    
    RectBody* rect_body = new RectBody();
    rect_body->set_rectangle({0,0,texture->width(),texture->height()});
    rect_body->set_dynamic(true);
    rect_body->set_mass(10);
    rect_body->set_restitution(0);
    test->set_physics_body(rect_body);
    
    Node* platform = new Node();
    platform->translate_by(0, 200);
    
    Texture* plat_sprite = new Texture();
    plat_sprite->open(std::string("plat.bmp"), renderer_);
    
    TextureBlock* plat_draw_block = new TextureBlock(renderer_, plat_sprite);
    platform->add_block(plat_draw_block);
    
    RectBody* plat_body = new RectBody();
    plat_body->set_rectangle({0,0,plat_sprite->width(),plat_sprite->height()});
    plat_body->set_mass(100);
    platform->set_physics_body(plat_body);
    
    world_->add_child(test);
    world_->add_child(platform);
    
    world_->set_name(std::string("World"));
    test->set_name(std::string("test"));
    platform->set_name(std::string("platform"));
    
#pragma mark -
    
    loop();
    end();
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
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void recursive_update(Cookie::Node& node, Cookie::Game& game)
{
    for(auto block = node.blocks_begin(); block != node.blocks_end(); ++block)
    {
        (*block)->update(node, game);
    }
#warning What happends when a block is updated before an other and there are dependencies between blocks?
    
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
    SDL_SetRenderDrawColor(renderer_->sdl_renderer(), 0, 0, 0, 255);
    SDL_RenderClear(renderer_->sdl_renderer());
    
    renderer_->renderBatch();
    
    SDL_RenderPresent(renderer_->sdl_renderer());
}