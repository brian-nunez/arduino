/**
* This was an example from the Arduino_Modulino samples.
* I modified it to be GREEN instead of BLUE.
*
* This was my first time doing anything with physical boards.
*
* Getting the LSP and configs were a bit of a pain, but eventually got it working.
*
* Updated my .zshrc file and neovim config
* .zshrc: https://github.com/brian-nunez/shell-scripts/commit/d0efc3310797fee20c6aebb705366782161f55c8
* neovim: https://github.com/brian-nunez/brian-nunez.nvim/commit/30578c742cce416ba00875a4f9f9687e21986dbf
*
*/

#include <Arduino_Modulino.h>

// Create a ModulinoPixels object
ModulinoPixels leds;

int brightness = 25;

void setup() {
  // set up the modulino items
  Modulino.begin();
  // get the LEDs
  leds.begin();
}

void loop() {
  // Set all 8 LEDs to blue color
  for (int i = 0; i < 8; i++) {
    // Set each LED (index, color, brightness)
    // Available colors: RED, BLUE, GREEN, VIOLET, WHITE
    leds.set(i, GREEN, brightness);
    // Update the physical LEDs with new settings
    leds.show();
  }
}
