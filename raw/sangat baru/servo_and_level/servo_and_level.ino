#include "config.h"
String dataIn;
String dt[8];
int i;
boolean parsing = false;


void setup() {
  Serial.begin(115200);
  dataIn = "";
  //servo attach to pin D3
  ser.attach(2);

  // wifi connection begin
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  //while (WiFi.status() != WL_CONNECTED) {
  ///delay(500);
  //}
  mqtt.subscribe(&servo);
}
void loop() {
  //connect to mqtt service

  MQTT_connect();
  unsigned long currentTime = millis();
  //subscibe data
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10000))) {
    if (subscription == &servo) {
      int servo_State = atoi((char *)servo.lastread);
      {
        if (servo_State == 1) {
          ser.write(180);
        }
        else
          ser.write(0);
      }
    }
  }

  //-----reading sensor and publish-----
  if (currentTime - previousTime >= eventInterval) {

    //reading sensor
    int sValue = analogRead(A0);
    byte mValue = map(sValue, 0, 1024, 0, 100);

    //tweaking some inconsistan reading value
    if (mValue > 100) {
      mValue = 100;
    }
    if (mValue < 50) {
      mValue = 50;
    }
    //publising data
    level.publish(mValue);

    if (Serial.available() > 0) { // check serial
      char inChar = (char)Serial.read();//variable inchar = hasil pembacaan serial
      dataIn += inChar; // dataIn + data inchar
      if (inChar == '\n') {
        parsing = true;
      }// jika charakter yag terbaca = \n maka melakukan parsing
    }

    if (parsing) {
      parsingData();
      parsing = false;
      dataIn = "";
    }
    //delay(20);

    int nilaiLC = dt[0].toInt();
    weight.publish(nilaiLC);
    previousTime = currentTime;
  }
}
