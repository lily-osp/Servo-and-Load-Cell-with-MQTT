# HX711 Load Cell Scale with I2C LCD Display and Servo Motor Control

This code is an example of how to use the HX711 load cell amplifier with an I2C LCD display and control a servo motor using an ESP8266 microcontroller. It uses the following libraries:
- HX711 library for reading the weight from the load cell 
- LiquidCrystal_I2C library for displaying the weight on the LCD
- Servo library for controlling the servo motor
- ESP8266WiFi and Adafruit_MQTT libraries for WiFi and MQTT functionality.

## Hardware Requirements
- HX711 load cell amplifier
- I2C LCD display
- Load cell sensor
- ESP8266 microcontroller
- Servo motor

## Pin Connections
- Connect the DOUT pin of the HX711 to pin 4 of the ESP8266
- Connect the SCK pin of the HX711 to pin 5 of the ESP8266
- Connect the SDA and SCL pins of the I2C LCD display to the respective SDA and SCL pins of the ESP8266
- Connect the servo motor to pin 2 of the ESP8266.

## Calibration
- The scale must be calibrated with known weights before use. 
- The value of `scale.set_scale(193.15)` is obtained by calibrating the scale. 
- This value is used to convert the raw data from the load cell to the weight in grams. 
- Adjust this value as necessary.

## WiFi and MQTT
- The ESP8266 connects to the WiFi network specified by the `WLAN_SSID` and `WLAN_PASS` variables in the `setup()` function.
- The device subscribes to the "servo" feed on Adafruit IO by calling `mqtt.subscribe(&servo);` in the `setup()` function and controls the servo motor based on the value received in the `loop()` function.
- The device publishes sensor data to the "level" feed on Adafruit IO by calling `level.publish(mValue);` in the `loop()` function.
- The code uses the `millis()` function to time the interval between publishing sensor data. The interval is specified by the `const unsigned long eventInterval = 3000;` which means the sensor data will be published every 3 seconds.
- The `MQTT_connect()` function is called to connect to the Adafruit IO server, it includes a retry mechanism in case of connection failure.

## Usage
1. Upload the code to the ESP8266 board
2. Open the serial monitor to check the weight readings
3. The LCD will display the weight in grams and "SISA PAKAN"
4. The Scale will be powered down after 2 seconds and powered up again for next reading
5. Make sure there is no weight on the scale before running the code

## Note
- The `scale.tare(50)` function is used to reset the scale to zero. The argument of this function is the number of readings to take while taring the scale.
- The `scale.get_units(25)` function is used to get the weight from the scale. The argument of this function is the number of readings to take while getting the weight.
- The `lcd.backlight()` function is used to turn on the backlight of the LCD.
- The `scale.power_down()` and `scale.power_up()` functions are used to save power and get accurate readings.
- The `ser.attach(2);` is used to attach the servo motor to pin 2 of the ESP8266.
- The `ser.write(0);` is used to set the initial position of the servo motor to 0
- The `ser.write(180);` is used to set the position of the servo motor to 180 when the value is 1 and `ser.write(0);` when the value is 0 in the `loop()` function.
