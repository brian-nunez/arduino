/**
* This project is reading analog data from a photo resistor on the A0 analog pin.
* 
* Setting this up was harder than the other ones. The code is smaller but the physical setup was more complex.
*
* Connections on breadboard to Arduino:
*   Photo Resistor: `J1` and `J2`
*   Jumper Wire 1 (Ground): `F5` to Arduino Digital `GND` Pin
*   Jumper Wire 2 (Voltage): `G1` to Arduino Power `5V`
*   Jumper Wire 3 (Analog Data): `G2` to Arduino Analog In `A0`
*   Resistor (10k): `H2` to `H5`
*
* With this configuration, I can now read the light near by.
*
*/
#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(A0);
  Serial.print("Light: ");
  Serial.println(light);
  delay(100);
}
