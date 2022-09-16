#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
String str;
HX711 scale;
//SoftwareSerial mySerial(9,10);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
    str =String ('*')+String (reading)+String("#");
Serial.println(str);
Serial1.println(str);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(1000);
  
}
