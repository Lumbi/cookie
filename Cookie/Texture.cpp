//
//  Texture.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-13.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Texture.h"
#include "Renderer.h"
#include "SDL_Conversion.h"

SDL_Surface* open_surface(std::string path, SDL_Surface* dst_surface);

Cookie::Texture::Texture()
{
    sdl_texture_ = NULL;
}

Cookie::Texture::~Texture()
{
    free();
}

Cookie::Bool Cookie::Texture::open(std::string path, const Cookie::Renderer* renderer)
{
    free();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* loaded_surface = open_surface(path.c_str(), renderer->sdl_surface());
    if(loaded_surface != NULL)
    {
        // Pink pixels will be transparent
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0, 0xFF ));
        new_texture = SDL_CreateTextureFromSurface(renderer->sdl_renderer(), loaded_surface);

        width_ = loaded_surface->w;
        height_ = loaded_surface->h;
    
        SDL_FreeSurface(loaded_surface);
    }
    sdl_texture_ = new_texture;
    return sdl_texture_ != NULL;
}

void Cookie::Texture::free()
{
    if(sdl_texture_ != NULL)
    {
        width_ = 0;
        height_ = 0;
        SDL_DestroyTexture(sdl_texture_);
        sdl_texture_ = NULL;
    }
}

Cookie::Float Cookie::Texture::width() const
{
    return width_;
}

Cookie::Float Cookie::Texture::height() const
{
    return height_;
}

void Cookie::Texture::set_color(Cookie::Color color)
{
    if(sdl_texture_ != NULL)
    {
        SDL_SetTextureColorMod(sdl_texture_, color.r * 255, color.g * 255, color.b * 255);
        SDL_SetTextureAlphaMod(sdl_texture_, color.a * 255);
    }
}

void Cookie::Texture::set_blend_mode(Cookie::TextureBlendMode blendmode)
{
    if(sdl_texture_)
    {
        SDL_SetTextureBlendMode(sdl_texture_, static_cast<SDL_BlendMode>(blendmode));
    }
}

void Cookie::Texture::set_alpha(Cookie::Float alpha)
{
    if(sdl_texture_ != NULL)
    {
        SDL_SetTextureAlphaMod(sdl_texture_, alpha * 255);
    }
}

void Cookie::Texture::render(Cookie::Renderer* renderer,
            const Cookie::Rect* src_rect,
            const Cookie::Rect* dst_rect,
            Cookie::TextureRenderFlip flip,
            Cookie::Float angle,
            const Cookie::Point* center)
{
    SDL_Rect sdl_src_rect;
    SDL_Rect sdl_dst_rect;
    SDL_Point sdl_center;
    
    if(src_rect != NULL) sdl_src_rect = Cookie::convert(*src_rect);
    if(dst_rect != NULL) sdl_dst_rect = Cookie::convert(*dst_rect);
    if(center != NULL) sdl_center = Cookie::convert(*center);
    
    SDL_RenderCopyEx(renderer->sdl_renderer(),
                     sdl_texture_,
                     src_rect != NULL ? &sdl_src_rect : NULL,
                     dst_rect != NULL ? &sdl_dst_rect : NULL,
                     angle,
                     center != NULL ? &sdl_center : NULL,
                     static_cast<SDL_RendererFlip>(flip));
}

SDL_Surface* open_surface(std::string path, SDL_Surface* dst_surface)
{
    SDL_Surface* optimized_surface = NULL;
    SDL_Surface* loaded_surface = SDL_LoadBMP( path.c_str() );
    if(loaded_surface == NULL)
    {
        printf( "Unable to load image %s: %s\n", path.c_str(), SDL_GetError() );
    }else{
        if(dst_surface != NULL)
        {
            optimized_surface = SDL_ConvertSurface( loaded_surface, dst_surface->format, NULL );
            if( optimized_surface == NULL )
            {
                printf( "Unable to optimize image %s: %s\n", path.c_str(), SDL_GetError() );
                return loaded_surface;
            }else{
                SDL_FreeSurface(loaded_surface);
                return optimized_surface;
            }
            
        }else{
            return loaded_surface;
        }
        
    }
    return NULL;
}