#include <Arduino_Modulino.h>

ModulinoKnob knob;
ModulinoPixels leds;

void setup() {
  Modulino.begin();

  leds.begin();
  knob.begin();
}

void loop() {
  leds.clear();

  onPress(&knob, [](){
    lightUpAllLEDs(&leds, BLUE, 20);
  });
  
  leds.show();
}
