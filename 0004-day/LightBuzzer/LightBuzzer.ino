/**
* This project combines the Modulino components with third party components. It gets the current light data and displays the levels on the ModulinoPixel.
*
* The knob is added here, but it's not really used for anything.
*
* I've started to get the hang of getting data through Serial and getting better at organizing the file. That has been the hardest part, getting data from one component then update another component while being in a loop.
*
* The internal handling feels the best to me where I use `millis`. It allows me to continue looping without blocking. Now I need to handle the "state" transitions better. Part of my struggle has to do with no knowing cpp. As I write more and google more, I'll get better.
*
*/
#include <Arduino.h>
#include <Arduino_Modulino.h>

ModulinoPixels leds;
ModulinoKnob knob;
ModulinoBuzzer buzzer;

int MAX_LEDS = 8;
int MIN_LEDS = 0;
int DEFAULT_BRIGHTNESS = 10;

int MAX_LIGHT_LEVEL = 1023;
int MIN_LIGHT_LEVEL = 0;

bool DEBUG_MODE = true;

int lastLEDState = 1024;

unsigned long lastUpdated = 0;
int UPDATE_INTERVAL = 100;

void PRINT_TELEMETRY_DATA(UART s = Serial) {
  if (!DEBUG_MODE) {
    return;
  }

  if (!Serial) {
    return;
  }

  unsigned long now = millis();

  if (!(now - lastUpdated >= UPDATE_INTERVAL)) {
    return;
  }

  // photo resistor
  int light = analogRead(A0);
  Serial.print("Light: ");
  Serial.println(light);

  // knob
  int8_t knobDirection = knob.getDirection();
  Serial.print("Knob Direction: ");
  Serial.println(knobDirection);

  int16_t knobValue = knob.get();
  Serial.print("Knob Value: ");
  Serial.println(knobValue);

  lastUpdated = now;
}

int clampIt(int value, int minVal, int maxVal) {
  return max(minVal, min(maxVal, value));
}

int readLightSensor() {
  int light = analogRead(A0);

  return clampIt(light, MIN_LIGHT_LEVEL, MAX_LIGHT_LEVEL);
}

int getLEDStateByLightLevel(int level) {
  return (level * MAX_LEDS) / MAX_LIGHT_LEVEL;
}

void setup() {
  Serial.begin(9600);

  Modulino.begin();

  leds.begin();
  knob.begin();
  buzzer.begin();
}

void loop() {
  PRINT_TELEMETRY_DATA();

  int light = readLightSensor();

  int ledsToLight = getLEDStateByLightLevel(light);

  if (lastLEDState != ledsToLight) {
    leds.clear();

    for (int i = 0; i < ledsToLight; i++) {
      leds.set(i, GREEN, DEFAULT_BRIGHTNESS);
    }

    leds.show();

    if (ledsToLight == 0) {
      buzzer.tone(800, 1000);
    } else {
      buzzer.tone(200, 100);
    }

    lastLEDState = ledsToLight;
  }
}
