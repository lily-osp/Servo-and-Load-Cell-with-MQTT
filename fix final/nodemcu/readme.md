# Servo Motor Control with WiFi and MQTT
This code is for a microcontroller (likely an ESP8266) that uses the Servo, WiFi and Adafruit MQTT library to control a servo motor, connect to a WiFi network and communicate with the Adafruit IO server.

## Servo Motor
- The servo motor is attached to pin 2, this is done by calling the `ser.attach(2);` in the `setup()` function.
- The initial position of the servo motor is set to 0, this is done by calling the `ser.write(0);` in the `setup()` function.
- The position of the servo motor is controlled by the value received from the "servo" feed on Adafruit IO, this is done by calling `ser.write(180);` when the value is 1 and `ser.write(0);` when the value is 0 in the `loop()` function.

## WiFi
- The device connects to the WiFi network specified by the `WLAN_SSID` and `WLAN_PASS` variables in the `setup()` function.
- The `loop()` function continuously check the status of the wifi connection by calling while `(WiFi.status() != WL_CONNECTED)`.

## Adafruit IO
- The Adafruit IO server credentials are specified by the `AIO_SERVER`, `AIO_SERVERPORT`, `AIO_USERNAME`, and `AIO_KEY` variables.
- The device subscribes to the "servo" feed by calling `mqtt.subscribe(&servo);` in the `setup()` function.
- The device publishes sensor data to the "level" feed by calling `level.publish(mValue);` in the `loop()` function.
- In the `loop()` function, it continuously check for new data from the "servo" feed by calling while `((subscription = mqtt.readSubscription(10000)))`.

## Timing
- The code uses the `millis()` function to time the interval between publishing sensor data.
- The interval is specified by the `const unsigned long eventInterval = 3000;` which means the sensor data will be published every 3 seconds.

## Function
- `setup()` function initializes the serial communication, attaches the servo to pin 2, connects to the WiFi network and subscribes to the "servo" feed on Adafruit IO.
- `loop()` function continuously checks for new servo data, updates the servo position, publishes sensor data to the "level" feed and check for new data from the "servo" feed on Adafruit IO.
- `MQTT_connect()` function is called to connect to the Adafruit IO server, it includes a retry mechanism in case of connection failure.

This code is a starting point for a project and may require additional modifications and adjustments to work with specific hardware and desired functionality.
