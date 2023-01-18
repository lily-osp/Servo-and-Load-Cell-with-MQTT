#include <Servo.h>
#include "HX711.h"
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Servo
Servo ser;
int pos = 0;

// Load cell
HX711 scale;
float weight;

// Millis timing
const unsigned long eventInterval = 3000;
unsigned long previousTime = 0;

// Wifi and MQTT config
#define WLAN_SSID       "azzar's phone"
#define WLAN_PASS       "password"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "Izmi"
#define AIO_KEY         "aio_yqlp10lxHXid8PGKx1DDaJlkP1Bl"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// MQTT subscribe
Adafruit_MQTT_Subscribe servo = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/servo");

// MQTT publish
Adafruit_MQTT_Publish weight = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/weight");

void setup() {
  Serial.begin(115200);
  
  // Servo
  ser.attach(2);
  ser.write(0);
  
  // Load cell
  scale.begin(A1, A2);
  scale.set_scale();
  scale.tare();
  
  // Wifi
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // MQTT
  mqtt.subscribe(&servo);
}

void loop() {
  // Connect to MQTT
  mqtt.connect();
  
  // Handle MQTT messages
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10000))) {
    if (subscription == &servo) {
      int servo_State = atoi((char *)servo.lastread);
      if (servo_State == 1) {
        ser.write(180);
      } else {
        ser.write(0);
      }
    }
  }
  
  // Millis timing
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= eventInterval) {
    // Read weight from load cell
    weight = scale.get_units();
    // Publish weight to MQTT
    weight.publish(weight);    
    // Display weight on Serial Monitor
    Serial.print("Weight: ");
    Serial.println(weight);
    previousTime = currentTime;
  }
  
  // Disconnect MQTT
  mqtt.disconnect();
  delay(20);
}

