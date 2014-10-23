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

inline Uint8 mix_samples(Uint8 a, Uint8 b, const SDL_AudioFormat& f) {
//    static Uint8 max = UINT8_MAX;
//    static Uint8 min = 1;

    return std::min(a+b, UINT8_MAX);
    
//    return
//    // If both samples are negative, mixed signal must have an amplitude between the lesser of A and B, and the minimum permissible negative amplitude
//    a < 0 && b < 0 ?
//    (a + b) - ((a * b)/min) :
//    
//    // If both samples are positive, mixed signal must have an amplitude between the greater of A and B, and the maximum permissible positive amplitude
//    ( a > 0 && b > 0 ?
//     (a + b) - ((a * b)/max)
//     
//     // If samples are on opposite sides of the 0-crossing, mixed signal should reflect that samples cancel each other out somewhat
//     :
//     a + b);
}

Cookie::AudioMixFilter::AudioMixFilter(SDL_AudioSpec audio_spec) : Cookie::AudioFilter(audio_spec)
{
    acc_buffer_ = NULL;
}


Cookie::AudioMixFilter::~AudioMixFilter()
{
    delete acc_buffer_;
}

void Cookie::AudioMixFilter::process(const Uint8* const buf, Uint32 len)
{
    if(len != 0)
    {
        if(acc_buffer_ == NULL)
        {
            acc_buffer_ = new Uint8[len];
            SDL_memset(acc_buffer_, 0, len);
            acc_len_ = len;
        }else if(acc_len_ < len){
            Uint8* acc_buffer_temp_ = new Uint8[len];
            SDL_memcpy(acc_buffer_temp_, acc_buffer_, acc_len_);
            SDL_memset(acc_buffer_temp_ + acc_len_, 0, len - acc_len_);
            delete acc_buffer_;
            acc_buffer_ = acc_buffer_temp_;
            acc_len_ = len;
        }
        printf("mixing:\n");
        for(int i = 0; i < 16; ++i) { printf("%d,",buf[i]); } printf("\n");
        printf("against:\n");
        for(int i = 0; i < 16; ++i) { printf("%d,",acc_buffer_[i]); } printf("\n");
        for(int i = 0; i < acc_len_; ++i)
        {
            if(i < len)
            {
                acc_buffer_[i] = mix_samples(acc_buffer_[i], buf[i], audio_spec_.format);
            }
        }
        //    for(int i = 0; i < 16; ++i) { printf("%d,",acc_buffer_[i]); } printf("\n");
    }
}

void Cookie::AudioMixFilter::flush()
{
    if(acc_len_ != 0)
    {
        out_->process(acc_buffer_, acc_len_);
        delete acc_buffer_;
        acc_buffer_ = NULL;
        acc_len_ = 0;
    }else{
        out_->process(NULL, 0);
    }
    
}