//
//  Sound.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-20.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "Sound.h"

Cookie::Sound::Sound(Cookie::Audio* audio)
{
    audio_ = audio;
    volume_ = 1.0f;
    buffer_length_ = 0;
    buffer_pos_ = 0;
    is_playing_ = false;
    channel_ = 0;
    sound_mutex_ = SDL_CreateMutex();
}

Cookie::Sound::~Sound()
{
    delete buffer_;
    SDL_DestroyMutex(sound_mutex_);
}

Cookie::Bool Cookie::Sound::open(std::string path)
{
    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
    
    if (SDL_LoadWAV(path.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL) {
        fprintf(stderr, "Could not open %s: %s\n", path.c_str(), SDL_GetError());
    } else {
        SDL_AudioCVT cvt;
        SDL_BuildAudioCVT(&cvt, wav_spec.format, wav_spec.channels, wav_spec.freq,
                          audio_->get_audio_spec().format,
                          audio_->get_audio_spec().channels,
                          audio_->get_audio_spec().freq);
        cvt.len = wav_length;
        cvt.buf = (Uint8 *) SDL_malloc(cvt.len * cvt.len_mult);
        SDL_memcpy(cvt.buf, wav_buffer, wav_length);
        SDL_ConvertAudio(&cvt);
        
        SDL_LockMutex(sound_mutex_);
        
        buffer_ = new Uint8[cvt.len * cvt.len_mult];
        SDL_memcpy(buffer_, cvt.buf, cvt.len * cvt.len_mult);
        buffer_length_ = cvt.len * cvt.len_mult;
        
        SDL_UnlockMutex(sound_mutex_);
        
        SDL_FreeWAV(wav_buffer);
        return true;
    }
    return false;
}

void Cookie::Sound::play(Cookie::Int loop)
{
    SDL_assert(loop > 0);
    
    SDL_LockMutex(sound_mutex_);
    if(!is_playing_){
        is_playing_ = true;
        loop_ = loop;
        audio_->queue(this);
    }
    SDL_UnlockMutex(sound_mutex_);
}

void Cookie::Sound::pause()
{
    SDL_LockMutex(sound_mutex_);
    is_playing_ = false;
    SDL_UnlockMutex(sound_mutex_);
}

void Cookie::Sound::stop()
{
    SDL_LockMutex(sound_mutex_);
    is_playing_ = false;
    buffer_pos_ = 0;
    loop_ = 0;
    SDL_UnlockMutex(sound_mutex_);
}

Cookie::Bool Cookie::Sound::is_playing() const
{
    return is_playing_;
}