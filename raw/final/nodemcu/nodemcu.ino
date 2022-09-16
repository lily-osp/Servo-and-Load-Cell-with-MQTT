#include "config.h"

void setup() {
  Serial.begin(115200);
  //while (!Serial) {
    //;
  //}
  //servo attach to pin D4
  ser.attach(2);
  ser.write(0);

  // wifi connection begin
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  //while (WiFi.status() != WL_CONNECTED) {
    //delay(500);
  //}
  mqtt.subscribe(&servo);
}
void loop() {

  //connect to mqtt service
  MQTT_connect();

  //millis
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

    if (Serial.available()) {
      weight.publish(Serial.read());
    }

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
    level.publish(mValue); //level
    previousTime = currentTime;
  }
  delay(20);
}
