/**
* This project was the first one that I did not use the modulino boards and connected third party components.
*
* There are two components.
* 1. A button
* 2. A passive buzzer
*
* When the button is clicked, it sends the data through pin 3. From there, we make invoke the tone function to activate the buzzer.
*/
#include <Arduino.h>

constexpr int BUTTON_INPUT_PIN = 3;
constexpr int PASSIVE_BUZZER_OUTPUT_PIN = 8;

void setup() {
  Serial.begin(9600);
  pinMode(PASSIVE_BUZZER_OUTPUT_PIN, OUTPUT);
  pinMode(BUTTON_INPUT_PIN, INPUT_PULLUP);

}

void loop() {
  PinStatus status = digitalRead(BUTTON_INPUT_PIN);
  if (status == HIGH) {
    Serial.println("HIGH");
  }

  if (status == LOW) {
    tone(PASSIVE_BUZZER_OUTPUT_PIN, 1000, 100);
    Serial.println("LOW");
  }

  Serial.println(status);
}
