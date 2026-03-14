#include <Arduino_Modulino.h>

ModulinoKnob knob;
ModulinoPixels leds;

constexpr short MAX_LEDS = 8;
constexpr short MIN_LEDS = 0;

int ledsCountToDisplay;

int clampIt(int value, int minVal = MIN_LEDS, int maxVal = MAX_LEDS) {
  return min(maxVal, max(minVal, value));
}

void setup() {
  Serial.begin(9600);

  Modulino.begin();
  knob.begin();
  leds.begin();

  ledsCountToDisplay = 0;
  knob.set(ledsCountToDisplay);
}

void loop() {
  handleKnob();
  renderLEDState();
}

void handleKnob() {
  int8_t direction = knob.getDirection();

  ledsCountToDisplay = clampIt(ledsCountToDisplay + direction);
}

void renderLEDState() {
  leds.clear();

  for (int i = 0; i < ledsCountToDisplay; i++) {
    leds.set(i, GREEN, 10);
  }

  leds.show();
}
