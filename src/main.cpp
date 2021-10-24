#include <Arduino.h>
#include <FastLED.h>

#include <board.h>

#include <rotary.h>
#include <led_matrix.h>

#include <animation.h>
#include <animations/hue.h>

// declare board components
rotary_t rot_top;
rotary_t rot_bottom;
bool top_clicked = false;
bool bottom_clicked = false;
led_matrix_t leds;

uint8_t brightness=255;

// animations
#define ANIMATION_CNT 1
animation_t* animations[ANIMATION_CNT] = {
  new animation_hue_t
};
size_t animations_idx=0;

void setup()
{
  Serial.begin(9600);
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
    brightness+=50;
    leds.set_brightness(brightness);
  }

  if (rot_top.pushed() && !top_clicked)
  {
    animations_idx=(animations_idx+1)%ANIMATION_CNT;
  }

  bottom_clicked=rot_bottom.pushed();
  top_clicked=rot_top.pushed();

  animations[animations_idx]->loop(leds);
}