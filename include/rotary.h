#pragma once

#include <Arduino.h>

/// A rotary encoder
struct rotary_t
{
    rotary_t() {}

    virtual ~rotary_t()=default;

    void setup(uint8_t dt, uint8_t clk, uint8_t sw)
    {
      _pin_dt = dt;
      _pin_clk = clk;
      _pin_sw = sw;

      _position = 0;
      _last_position = _position;
      _pushed = false;

      pinMode(_pin_clk,INPUT);
      pinMode(_pin_dt,INPUT);
      pinMode(_pin_sw,INPUT_PULLUP);

      _last_clk = digitalRead(_pin_clk);
      _last_sw = digitalRead(_pin_sw);
    }

    void read()
    {
      _last_position = _position;
      _last_pushed = _pushed;

      // If last and current state of CLK are different, then pulse occurred
      int cur_clk = digitalRead(_pin_clk);
      if (cur_clk != _last_clk && cur_clk == HIGH)
      {
        int cur_dt = digitalRead(_pin_dt);
        // If the DT state is different than the CLK state then the encoder is rotating CCW so decrement
        if (cur_dt != cur_clk) --_position;
        else ++_position;
        Serial.print("position changed: ");
        Serial.println(_position);
      }
      _last_clk = cur_clk;

      // read button state
      int cur_sw = digitalRead(_pin_sw);
      _pushed = (cur_sw == LOW && _last_sw == HIGH);
      _last_sw = cur_sw;
      if (_pushed)
      {
        Serial.println("pushed");
      }
    }

    int pos() const
    {
      return _position;
    }

    bool pos_changed() const
    {
      return _last_position != _position;
    }

    bool pushed() const
    {
      return _pushed;
    }

    bool pushed_changed() const
    {
      return _pushed != _last_pushed;
    }

private:
    uint8_t _pin_dt;
    uint8_t _pin_clk;
    uint8_t _pin_sw;

    int _position;
    bool _pushed;
    int _last_position;
    bool _last_pushed;

    int _last_clk;
    int _last_sw;
};