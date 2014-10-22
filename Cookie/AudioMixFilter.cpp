//
//  AudioMixFilter.cpp
//  Cookie
//
//  Created by Gabriel Lumbi on 2014-10-21.
//  Copyright (c) 2014 Gabriel Lumbi. All rights reserved.
//

#include "AudioMixFilter.h"
#include <cmath>

//#define SDL_AUDIO_MASK_BITSIZE       (0xFF)
//#define SDL_AUDIO_MASK_DATATYPE      (1<<8)
//#define SDL_AUDIO_MASK_ENDIAN        (1<<12)
//#define SDL_AUDIO_MASK_SIGNED        (1<<15)
//#define SDL_AUDIO_BITSIZE(x)         (x & SDL_AUDIO_MASK_BITSIZE)
//#define SDL_AUDIO_ISFLOAT(x)         (x & SDL_AUDIO_MASK_DATATYPE)
//#define SDL_AUDIO_ISBIGENDIAN(x)     (x & SDL_AUDIO_MASK_ENDIAN)
//#define SDL_AUDIO_ISSIGNED(x)        (x & SDL_AUDIO_MASK_SIGNED)
//#define SDL_AUDIO_ISINT(x)           (!SDL_AUDIO_ISFLOAT(x))
//#define SDL_AUDIO_ISLITTLEENDIAN(x)  (!SDL_AUDIO_ISBIGENDIAN(x))
//#define SDL_AUDIO_ISUNSIGNED(x)      (!SDL_AUDIO_ISSIGNED(x))

template<typename T>
T clamp(const T& value, T min, T max)
{
    if(value < min)
    {
        return min;
    }else if(value > max)
    {
        return max;
    }
    return value;
}

#warning TODO find max & min values for audio format?

inline Uint8 format_max(const SDL_AudioFormat& format)
{
    if(SDL_AUDIO_ISFLOAT(format))
    {
        if(SDL_AUDIO_ISBIGENDIAN(format))
        {
            return 1;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}

inline Uint8 format_min(const SDL_AudioFormat& format)
{
    return 0;
}

Cookie::AudioMixFilter::AudioMixFilter(SDL_AudioSpec audio_spec) : Cookie::AudioVolumeFilter(audio_spec)
{
    acc_buffer_ = NULL;
}


Cookie::AudioMixFilter::~AudioMixFilter()
{
    delete acc_buffer_;
}

void Cookie::AudioMixFilter::process(const Uint8* const buf, Uint32 len)
{
    printf("AudioMixFilter\n");
    if(acc_buffer_ == NULL)
    {
        acc_buffer_ = new Uint8[len];
        acc_len_ = len;
    }else if(acc_len_ < len){
        Uint8* acc_buffer_temp_ = new Uint8[len];
        SDL_memcpy(acc_buffer_temp_, acc_buffer_, acc_len_);
        SDL_memset(acc_buffer_temp_ + acc_len_, 0, len - acc_len_);
        delete acc_buffer_;
        acc_buffer_ = acc_buffer_temp_;
        acc_len_ = len;
    }
    
    for(int i = 0; i < acc_len_; ++i)
    {
        if(i < len)
        {
#warning DANGER! no clamping in sight!
            acc_buffer_[i] = acc_buffer_[i]+buf[i];
        }
    }
}

void Cookie::AudioMixFilter::flush()
{
    out_->process(acc_buffer_, acc_len_);
    delete acc_buffer_;
    acc_buffer_ = NULL;
    acc_len_ = 0;
}