#include <math.h>
#include <Arduino.h>
#include <Arduino_Modulino.h>

int THERMISTOR_PIN = A0;
int MAX_THEMISTOR_LEVEL = 1023;
int MIN_THEMISTOR_LEVEL = 0;

bool DEBUG_MODE = true;

unsigned long telemetryLastUpdated = 0;
int TELEMETRY_UPDATE_INTERVAL = 100;

void PRINT_TELEMETRY_DATA(UART s = Serial) {
  if (!DEBUG_MODE) {
    return;
  }

  if (!Serial) {
    return;
  }

  unsigned long now = millis();

  if (!(now - telemetryLastUpdated >= TELEMETRY_UPDATE_INTERVAL)) {
    return;
  }

  // photo resistor
  int light = analogRead(THERMISTOR_PIN);
  Serial.print("Light: ");
  Serial.println(light);

  telemetryLastUpdated = now;
}

int clampIt(int value, int minVal, int maxVal) {
  return max(minVal, min(maxVal, value));
}

float temperatureF(int analogValue) {
  float resistance = 10000.0 / ((1023.0 / (float)analogValue) - 1.0);

  float temperatureK =
    1.0 / ((1.0 / (22.0 + 273.15)) + (1.0 / 3950.0) * log(resistance / 67000.0));

  float temperatureC = temperatureK - 273.15;

  return temperatureC * 9.0 / 5.0 + 32.0;
}

int readThemistorSensor() {
  int value = analogRead(THERMISTOR_PIN);

  return clampIt(value, MIN_THEMISTOR_LEVEL, MAX_THEMISTOR_LEVEL);
}

int readThermistorTemperature() {
  int value = readThemistorSensor();

  return temperatureF(value);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int tempF = readThermistorTemperature();

  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.println(" °F");
}
