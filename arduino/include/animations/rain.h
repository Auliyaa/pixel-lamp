#pragma once

#include <animation.h>
#include <board.h>

class animation_rain_t: public cs_animation_t<50>
{
public:
    animation_rain_t()
    {
        memset(_droplets,SIZE_MAX,LED_ARRAY_WIDTH*sizeof(size_t));
    }

protected:
    virtual void step(led_matrix_t& leds)
    {
        leds.reset();
        for(size_t xx=0; xx<LED_ARRAY_WIDTH; ++xx)
        {
            // remove droplets that already reached bottom position
            if (_droplets[xx] == 0)
            {
                _droplets[xx] = SIZE_MAX;
            }

            // randomly spawn new droplets
            else if (_droplets[xx] == SIZE_MAX)
            {
                if (random(50) == 0)
                {
                    _droplets[xx]=LED_ARRAY_HEIGHT-1;
                }
            }

            else
            {
                --_droplets[xx];
            }

            // draw droplets on the led matrix
            if (_droplets[xx] != SIZE_MAX)
            {
                leds[xx][_droplets[xx]] = CRGB(255,255,255);
            }
        }
    }

private:
    size_t _droplets[LED_ARRAY_WIDTH];
};