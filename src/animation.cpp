#include <animation.h>

void animation_t::setup(led_matrix_t& leds)
{
    _last_ms = millis();
    step(leds,0);
}

void animation_t::loop(led_matrix_t& leds)
{
    leds.reset();
    if (step(leds,_last_ms))
    {
        _last_ms = millis();
        leds.show();
    }
}