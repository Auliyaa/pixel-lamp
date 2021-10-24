#pragma once

#include <led_matrix.h>

class animation_t
{
public:
    void setup(led_matrix_t&);
    void loop(led_matrix_t&);

protected:
    virtual bool step(led_matrix_t&,unsigned long last_time);

private:
    unsigned long _last_ms;
};

template<unsigned long __period>
class cs_animation_t: public animation_t
{
protected:
    virtual bool step(led_matrix_t& leds,unsigned long last_time) final override
    {
        if (millis()-last_time >=__period)
        {
            step(leds);
            return true;
        }
        return false;
    }

    virtual void step(led_matrix_t&)=0;
};