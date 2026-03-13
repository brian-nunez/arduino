/**
* Day 1
*
* I got this cool looking light cycle going.
*
* Took me way longer than it should have, but I don't know c++ and my brain is rotted.
*
*/
#include <Arduino_Modulino.h>

ModulinoPixels leds;

int BRIGHTNESS = 10;
int DELAY = 500;
int NUM_OF_LIGHTS = 8;
ModulinoColor* COLORS[] = {
  &RED, &BLUE, &GREEN, &YELLOW, &CYAN, &BLACK, &VIOLET, &WHITE
};
int COLOR_OFFSET = 0;

void setup() {
  Modulino.begin();
  leds.begin();
}

void loop() {
  for (int i = 0; i < NUM_OF_LIGHTS; i++) {
    int idx = (i + COLOR_OFFSET) % NUM_OF_LIGHTS;
    leds.set(i, *COLORS[idx], BRIGHTNESS);
  }

  COLOR_OFFSET = (COLOR_OFFSET + 1) % NUM_OF_LIGHTS;

  leds.show();
  delay(DELAY);
}
