#pragma once

#include <animation.h>
#include <board.h>

class animation_horizontal_hue_t: public cs_animation_t<50>
{
public:
    animation_horizontal_hue_t()
    {
        float hue_step = 255. / float(LED_ARRAY_WIDTH);
        float hue=0.;
        for (size_t xx=0; xx < LED_ARRAY_WIDTH; ++xx)
        {
            _hue[xx] = hue;
            hue += hue_step;
        }
    }

protected:
    virtual void step(led_matrix_t& leds)
    {
        for (size_t xx=0; xx < LED_ARRAY_WIDTH; ++xx)
        {
            CHSV hsv(_hue[xx],255,255);
            CRGB rgb;
            hsv2rgb_rainbow(hsv,rgb);
            for (size_t yy=0; yy < LED_ARRAY_HEIGHT; ++yy)
            {
                leds[xx][yy] = rgb;
            }
            _hue[xx] = (_hue[xx]+1)%255;
        }
    }

private:
    uint8_t _hue[LED_ARRAY_WIDTH];
};

class animation_vertical_hue_t: public cs_animation_t<50>
{
public:
    animation_vertical_hue_t()
    {
        float hue_step = 255. / float(LED_ARRAY_HEIGHT);
        float hue=0.;
        for (size_t yy=0; yy < LED_ARRAY_HEIGHT; ++yy)
        {
            _hue[yy] = hue;
            hue += hue_step;
        }
    }

protected:
    virtual void step(led_matrix_t& leds)
    {
        for (size_t yy=0; yy < LED_ARRAY_HEIGHT; ++yy)
        {
            CHSV hsv(_hue[yy],255,255);
            CRGB rgb;
            hsv2rgb_rainbow(hsv,rgb);
            for (size_t xx=0; xx < LED_ARRAY_WIDTH; ++xx)
            {
                leds[xx][yy] = rgb;
            }
            _hue[yy] = (_hue[yy]+1)%255;
        }
    }

private:
    uint8_t _hue[LED_ARRAY_HEIGHT];
};