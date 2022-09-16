#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
String str;
HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(193.15);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(50);
}

void loop() {
  float reading = scale.get_units(25);
  if (reading <= 0.1) {
    reading = 0;
  }
  //Serial.print("HX711 reading: ");
  //Serial.println(reading);
  str = String ('*') + String (reading) + String("#");
  Serial.println(str);

  delay(1000);

}
