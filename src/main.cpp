#include <Arduino.h>
#include <FastLED.h>

#include <rotary.h>
#include <led_matrix.h>
#include <board.h>

// rotary_t rot_brightness{ROT_BRIGHTNESS_DT, ROT_BRIGHTNESS_CLK, ROT_BRIGHTNESS_SW};

led_matrix_t leds;

int hue[LED_ARRAY_WIDTH];

void setup()
{
  Serial.begin(9600);
  leds.setup();

  // rot_brightness.setup();
  memset(hue,0,LED_ARRAY_WIDTH);

  float h=0;
  float hs=255/LED_ARRAY_WIDTH;
  for (size_t xx=0; xx<LED_ARRAY_WIDTH; ++xx)
  {
    hue[xx] = h;
    h+=hs;
  }
}


void loop()
{
  leds.reset();

  for (size_t xx=0; xx<LED_ARRAY_WIDTH; ++xx)
  {
    int sat=175;
    for (size_t yy=0; yy<LED_ARRAY_HEIGHT; ++yy)
    {
      CHSV hsv(hue[xx],sat,255);
      CRGB rgb;
      hsv2rgb_rainbow(hsv,rgb);

      leds[xx][yy]=rgb;

      sat += 10;
    }

    hue[xx]=(hue[xx]+10)%255;
  }

  leds.show();
  delay(100);
}