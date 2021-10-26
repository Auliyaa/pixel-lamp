#include <Arduino.h>
#include <FastLED.h>

#include <board.h>

#include <rotary.h>
#include <led_matrix.h>

#include <animation.h>
#include <animations/hue.h>
#include <animations/rain.h>
#include <animations/evs.h>
#include <animations/rainbow.h>
#include <animations/pong.h>

// declare board components
rotary_t rot_top;
rotary_t rot_bottom;
bool top_clicked = false;
bool bottom_clicked = false;
led_matrix_t leds;

#define BRIGHTNESS_CNT 6
uint8_t brightness[BRIGHTNESS_CNT] = {
  0,
  50,
  100,
  150,
  200,
  250
};
size_t brightness_idx=5;

// animations
#define ANIMATION_CNT 5
animation_t* animations[ANIMATION_CNT] = {
  new animation_rainbow_t,
  new animation_hue_t,
  new animation_pong_t,
  new animation_rain_t,
  new evs_t,
};
size_t animations_idx=0;

void setup()
{
  Serial.begin(9600);
  // init rseed from an unconnected pin signal noise
  randomSeed(analogRead(0));

  rot_top.setup(ROT_TOP_DT,ROT_TOP_CLK,ROT_TOP_SW);
  rot_bottom.setup(ROT_BOTTOM_DT,ROT_BOTTOM_CLK,ROT_BOTTOM_SW);
  leds.setup();

  for (size_t ii=0; ii<ANIMATION_CNT; ++ii)
  {
    animations[ii]->setup(leds);
  }
}

void loop()
{
  // handle rotaries
  rot_bottom.read();
  rot_top.read();

  if (rot_bottom.pushed() && !bottom_clicked)
  {
    // bottom button pushed
    brightness_idx = (brightness_idx+1)%BRIGHTNESS_CNT;
    leds.set_brightness(brightness[brightness_idx]);
  }

  if (rot_top.pushed() && !top_clicked)
  {
    animations_idx=(animations_idx+1)%ANIMATION_CNT;
  }

  bottom_clicked=rot_bottom.pushed();
  top_clicked=rot_top.pushed();

  animations[animations_idx]->loop(leds);
}