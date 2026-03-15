#include <Arduino_Modulino.h>

ModulinoKnob knob;
ModulinoPixels leds;
ModulinoBuzzer buzzer;

int MAX_LEDS = 8;
int MIN_LEDS = 0;
int currentLEDCount = 0;
bool isOn = false;

unsigned long lastUpdated = 0;
unsigned long UPDATE_INTERVAL = 100;

int clampIt(int value, int minVal = MIN_LEDS, int maxVal = MAX_LEDS) {
  return min(maxVal, max(minVal, value));
}

void lightUpAllLEDs(ModulinoPixels* leds, int count, ModulinoColor color, uint8_t brightness) {
  for (int i = 0; i < count; i++) {
    leds->set(i, color, brightness);
  }
}

void resetModules() {
  knob.set(0);
  buzzer.noTone();
  leds.clear();
  lightUpAllLEDs(&leds, 8, RED, 10);
  leds.show();
  isOn = false;
}

void setup() {
  Serial.begin(9600);
  Modulino.begin();

  knob.begin();
  leds.begin();
  buzzer.begin();

  resetModules();
}

void loop() {
  if (knob.isPressed()) {
    isOn = !isOn;
    Serial.print("Is On: ");
    Serial.println(isOn);
    delay(200);
  }

  if (!isOn) {
    resetModules();
    return;
  }
  
  int16_t knobValue = knob.get();
  short knobDirection = knob.getDirection();

  currentLEDCount = clampIt(currentLEDCount + knobDirection);

  leds.clear();
  lightUpAllLEDs(&leds, currentLEDCount, GREEN, 1);
  leds.show();

  unsigned long now = millis();
  if (now - lastUpdated >= UPDATE_INTERVAL) {
    int tone = currentLEDCount * 100;
    buzzer.tone(tone, 100);
    lastUpdated = now;
  }
}

