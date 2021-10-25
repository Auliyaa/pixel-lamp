#pragma once

#include <animation.h>
#include <board.h>

class animation_rainbow_t: public cs_animation_t<10>
{
public:
    animation_rainbow_t()
    {
        _hue_step = 255. / 30000.;
        _hue=0;
    }

protected:
    virtual void step(led_matrix_t& leds)
    {
        CHSV hsv(_hue,255,255);
        CRGB rgb;
        hsv2rgb_rainbow(hsv,rgb);
        for (size_t xx=0; xx < LED_ARRAY_WIDTH; ++xx)
        {
            for (size_t yy=0; yy < LED_ARRAY_HEIGHT; ++yy)
            {
                leds[xx][yy] = rgb;
            }
        }

        // change directions
        if (_hue + _hue_step > 255. || _hue +_hue_step < 0)
        {
            _hue_step *= -1;
        }
        _hue+=_hue_step;
    }

private:
    float _hue;
    float _hue_step;
};