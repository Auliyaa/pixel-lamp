#pragma once

#include <Arduino.h>
#include <FastLED.h>

struct led_col_t
{
    led_col_t(CRGB*);
    virtual CRGB& operator[](size_t);

    CRGB* d;
};

struct led_col_r_t: public led_col_t
{
    led_col_r_t(CRGB*);
    virtual CRGB& operator[](size_t) final override;
};

class led_matrix_t
{
public:
    led_matrix_t();
    virtual ~led_matrix_t() = default;

    void setup();
    led_col_t& operator[](size_t);

    void reset();
    void set_brightness(uint8_t) const;
    void show() const;

private:
    CRGB* _leds;
    led_col_t** _cols;
};