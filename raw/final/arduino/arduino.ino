#include "HX711.h"
//#include <SoftwareSerial.h>

const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
HX711 scale;
//SoftwareSerial espSerial(5, 6);
String str;

void setup() {
  Serial.begin(115200);
  //espSerial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(193.15);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(50);               // reset the scale to 0
}

void loop() {
  float berat = scale.get_units(25);
  if (berat<0){
    berat = 0;
  }
  if (berat>250){
    berat = 250;
  }
  str = String(berat, 1);
  Serial.println(str);
  //espSerial.println(str);
}
