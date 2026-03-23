#include <Arduino.h>
#include <Arduino_Modulino.h>

unsigned long lastUpdated = 0;
int UPDATE_INTERVAL = 100;

bool DEBUG_MODE = false;

ModulinoKnob knob;

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
