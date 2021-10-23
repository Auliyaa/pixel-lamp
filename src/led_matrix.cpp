#include <led_matrix.h>

#include <board.h>

led_col_t::led_col_t(CRGB* d)
{
    this->d = d;
}

CRGB& led_col_t::operator[](size_t yy)
{
    return d[yy];
}

led_col_r_t::led_col_r_t(CRGB* d)
: led_col_t(d)
{
}

CRGB& led_col_r_t::operator[](size_t yy)
{
    return d[LED_ARRAY_HEIGHT-1-yy];
}

led_matrix_t::led_matrix_t()
{
}

void led_matrix_t::setup()
{
  size_t led_cnt = LED_PIN_CNT * LED_PER_PIN;

  _leds = new CRGB[led_cnt];
  memset(_leds,0,sizeof(CRGB)*led_cnt);
  _cols = new led_col_t*[LED_ARRAY_WIDTH];
  for (size_t xx=0; xx < LED_ARRAY_WIDTH; ++xx)
  {
      if (xx%2==0)  _cols[xx] = new led_col_t(_leds+xx*LED_ARRAY_HEIGHT);
      else _cols[xx] = new led_col_r_t(_leds+xx*LED_ARRAY_HEIGHT);
  }

  FastLED.addLeds<WS2812B, LED_PIN_0, RGB>(_leds, LED_PER_PIN);
  FastLED.addLeds<WS2812B, LED_PIN_1, RGB>(_leds+LED_PER_PIN, LED_PER_PIN);
  FastLED.addLeds<WS2812B, LED_PIN_2, RGB>(_leds+LED_PER_PIN*2, LED_PER_PIN);
  FastLED.addLeds<WS2812B, LED_PIN_3, RGB>(_leds+LED_PER_PIN*3, LED_PER_PIN);
}

led_col_t& led_matrix_t::operator[](size_t xx)
{
    if (xx>=0 && xx<=3)   return *_cols[3-xx];
    if (xx>=4 && xx<=7)   return *_cols[7-xx+4];
    if (xx>=8 && xx<=11)  return *_cols[xx];
    if (xx>=12 && xx<=15) return *_cols[15-xx+12];
}

void led_matrix_t::reset()
{
    memset(_leds,0,sizeof(CRGB)*LED_CNT);
}

void led_matrix_t::show() const
{
    FastLED.show();
}