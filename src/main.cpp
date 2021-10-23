#include <Arduino.h>
#include <FastLED.h>

#include <rotary.h>
#include <led_matrix.h>
#include <board.h>

// declare board components
rotary_t rot_top;
rotary_t rot_bottom;
led_matrix_t leds;

void setup()
{
  Serial.begin(9600);
  rot_top.setup(ROT_TOP_DT,ROT_TOP_CLK,ROT_TOP_SW);
  rot_bottom.setup(ROT_BOTTOM_DT,ROT_BOTTOM_CLK,ROT_BOTTOM_SW);
  leds.setup();
}

size_t xx=0;
void loop()
{
  // handle bottom rotary
  rot_bottom.read();
  if (rot_bottom.pos_changed() && rot_bottom.pos() <= 255 && rot_bottom.pos() >=0)
  {
    Serial.print("setting brightness to ");
    Serial.println(rot_bottom.pos());
    leds.set_brightness(rot_bottom.pos());
  }

  leds.reset();
  leds[xx][0] = CRGB(255,0,0);
  xx=(xx+1)%LED_ARRAY_WIDTH;
  leds.show();

  delay(20);
}