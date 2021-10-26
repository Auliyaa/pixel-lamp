#pragma once

#include <animation.h>
#include <board.h>

template<uint8_t r, uint8_t g, uint8_t b>
class animation_static_color_t: public cs_animation_t<3600>
{
public:
    animation_static_color_t()
    {
    }

protected:
    virtual void step(led_matrix_t& leds)
    {
        CRGB rgb(r,g,b);
        for (size_t xx=0; xx < LED_ARRAY_WIDTH; ++xx)
        {
            for (size_t yy=0; yy < LED_ARRAY_HEIGHT; ++yy)
            {
                leds[xx][yy] = rgb;
            }
        }
    }
};