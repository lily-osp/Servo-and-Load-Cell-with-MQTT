//define pin
#include <Servo.h>
Servo ser;

//serial preparation
SoftwareSerial mySerial(14,12);

//initial data value
int pos = 0;
int val = 0 ;

//library
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//millis timing
const unsigned long eventInterval = 3000; //1000 for 1s
unsigned long previousTime = 0;

//wifi config
#define WLAN_SSID       "azzar's phone"             // Your SSID
#define WLAN_PASS       "password"         // Your password

//aio config
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "Izmi"
#define AIO_KEY         "aio_yqlp10lxHXid8PGKx1DDaJlkP1Bl"

//WIFI CLIENT
WiFiClient client;

//starting mqtt services
void MQTT_connect();

//mqtt client
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
//mqtt subscribe
Adafruit_MQTT_Subscribe servo = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/servo");
//mqtt publish
Adafruit_MQTT_Publish level   = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/level");
//mqtt publish
Adafruit_MQTT_Publish loadcell  = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/loadcell");
