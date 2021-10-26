#pragma once

#include <animation.h>
#include <board.h>

struct animation_step_t
{
    unsigned long delay;
    uint8_t data[LED_ARRAY_HEIGHT*LED_ARRAY_WIDTH*3];
};

class animation_bmp_t: public animation_t
{
public:
    animation_bmp_t()
    : _idx{0}
    {
    }

protected:
    virtual bool step(led_matrix_t& leds, unsigned long last_time)
    {
        auto c = get(_idx);
        if (millis()-last_time > c.delay)
        {
            // Apply diff
            leds.reset();
            for (size_t xx=0; xx<LED_ARRAY_WIDTH; ++xx)
            {
                for (size_t yy=0; yy<LED_ARRAY_HEIGHT; ++yy)
                {
                    size_t idx = 3*(xx*LED_ARRAY_HEIGHT+yy);
                    leds[xx][yy] = CRGB(c.data[idx],c.data[idx+1],c.data[idx+2]);
                }
            }
            _idx = (_idx+1)%size();

            return true;
        }


        return false;
    }

    virtual animation_step_t get(size_t idx) const=0;
    virtual size_t size() const=0;

private:
    size_t _idx;
};

template<size_t __period>
class animation_rotating_bmp_t: public cs_animation_t<__period>
{
public:
    animation_rotating_bmp_t()
    : _shift{0}
    {
    }

protected:
    virtual void step(led_matrix_t& leds)
    {
        auto c = get(0);
        // Apply diff
        leds.reset();
        size_t sxx=0;
        for (size_t xx=0; xx<LED_ARRAY_WIDTH; ++xx)
        {
            sxx=(xx-_shift)%LED_ARRAY_WIDTH;
            for (size_t yy=0; yy<LED_ARRAY_HEIGHT; ++yy)
            {
                size_t idx = 3*(xx*LED_ARRAY_HEIGHT+yy);
                leds[sxx][yy] = CRGB(c.data[idx],c.data[idx+1],c.data[idx+2]);
            }
        }
        _shift = (_shift+1)%LED_ARRAY_WIDTH;
    }

    virtual animation_step_t get(size_t idx) const=0;
    virtual size_t size() const=0;

private:
    size_t _shift;
};