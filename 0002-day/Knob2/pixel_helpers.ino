#include <Arduino_Modulino.h>

void lightUpAllLEDs(ModulinoPixels* leds, ModulinoColor color, uint8_t brightness) {
  leds->clear();

  for (int i = 0; i < 8; i++) {
    leds->set(i, color, brightness);
  }

  leds->show();
}
