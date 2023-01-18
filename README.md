## Servo and Load Cell with MQTT

This code is for an Arduino project that uses a servo and a load cell sensor, as well as an MQTT connection to remotely control the servo and read the weight value from the load cell sensor.

### Hardware
- Arduino board (e.g. Uno, Mega, etc.)
- Servo motor
- Load cell sensor
- HX711 amplifier
- ESP8266 WiFi module (if your arduino board doesn't have wifi built-in)

### Libraries
- `Servo.h`: for controlling the servo motor
- `HX711.h`: for reading data from the load cell sensor
- `ESP8266WiFi.h`: for connecting to WiFi
- `Adafruit_MQTT.h` and `Adafruit_MQTT_Client.h`: for connecting to MQTT

### Wiring
- Connect the servo motor to pin 2 on the Arduino board.
- Connect the load cell sensor to the HX711 amplifier and then connect the amplifier to the A1 and A2 pins on the Arduino board.
- Connect the ESP8266 WiFi module to the Arduino board and make sure to upload the firmware to the ESP8266.

### MQTT
- Change the following MQTT variables in the code with your own values:
  - `WLAN_SSID`: the name of your WiFi network
  - `WLAN_PASS`: the password of your WiFi network
  - `AIO_SERVER`: the server address for the MQTT broker (e.g. "io.adafruit.com")
  - `AIO_SERVERPORT`: the port number for the MQTT broker (e.g. 1883)
  - `AIO_USERNAME`: your username for the MQTT broker
  - `AIO_KEY`: your key for the MQTT broker
- The code subscribes to a topic called "servo" and publishes to a topic called "weight". Make sure these topics match the ones you have set up on your MQTT broker.
- The code also uses the millis() function for timing the data reading and publishing. You can adjust the `eventInterval` variable to change the frequency of the data reading and publishing.

### Usage
- Upload the code to your Arduino board and open the Serial Monitor.
- Connect the Arduino board to your WiFi network and make sure the ESP8266 is working properly.
- Send a "1" or "0" to the "servo" topic to control the servo.
- Monitor the "weight" topic to see the weight value from the load cell sensor.

### Load Cell Sensor
- The code uses the HX711 library to read data from the load cell sensor.
- `scale.set_scale();` is a function that sets the scale factor for the load cell sensor. This is used to calibrate the sensor to a known weight, so that accurate weight measurements can be taken. The scale factor is the number of units per gram.
- `scale.tare();` is a function that sets the current weight as the zero point for the sensor. This is used to remove the weight of any objects that are already on the load cell sensor, before taking a measurement.
- Both `scale.set_scale();` and `scale.tare();` are called in the setup function to initialize the load cell sensor and set the scale factor and zero point, so that accurate weight measurements can be taken.
- You can adjust the scale factor according to your load cell sensor specifications and your desired measurement unit.
- Also you can use `scale.set_offset(offset)` to set an offset value to the readings, which can be useful when you want to add a constant value to the reading.
