#pragma once

#include <Arduino.h>

/// A rotary encoder
struct rotary_t
{
    rotary_t(uint8_t dt, uint8_t clk, uint8_t sw)
    :   _pin_dt{dt}, _pin_clk{clk}, _pin_sw{sw}
    {
    }

    virtual ~rotary_t()=default;

    void setup()
    {
        _position = 0;
        _pushed = false;

        pinMode(_pin_clk,INPUT);
        pinMode(_pin_dt,INPUT);
        pinMode(_pin_sw, INPUT_PULLUP);

        _last_clk = digitalRead(_pin_clk);
        _last_sw = digitalRead(_pin_sw);
    }

    void read()
    {
      // If last and current state of CLK are different, then pulse occurred
      int cur_clk = digitalRead(_pin_clk);
      if (cur_clk != _last_clk && cur_clk == HIGH)
      {
        int cur_dt = digitalRead(_pin_dt);
        // If the DT state is different than the CLK state then the encoder is rotating CCW so decrement
        if (cur_dt != cur_clk) --_position;
        else ++_position;
      }
      _last_clk = cur_clk;

      // read button state
      int cur_sw = digitalRead(_pin_sw);
      _pushed = (cur_sw == LOW && _last_sw == HIGH);
      _last_sw = cur_sw;
    }

    int pos() const
    {
      return _position;
    }

    bool pushed() const
    {
      return _pushed;
    }

private:
    uint8_t _pin_dt;
    uint8_t _pin_clk;
    uint8_t _pin_sw;

    int _position;
    bool _pushed;

    int _last_clk;
    int _last_sw;
};