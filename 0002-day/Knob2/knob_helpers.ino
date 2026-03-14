#include <Arduino_Modulino.h>

void onPress(ModulinoKnob* knob, void (*fn)()) {
  if (knob->isPressed()) {
    fn();
  }
}
