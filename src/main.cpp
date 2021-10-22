#include <Arduino.h>

#include <rotary.h>
#include <pins.h>

rotary_t rot_brightness{ROT_BRIGHTNESS_DT, ROT_BRIGHTNESS_CLK, ROT_BRIGHTNESS_SW};

void setup()
{
  Serial.begin(9600);
  rot_brightness.setup();
}

void loop()
{
  
}