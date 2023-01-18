# HX711 Load Cell Scale with I2C LCD Display
This code is an example of how to use the HX711 load cell amplifier with an I2C LCD display. It uses the HX711 library and the LiquidCrystal_I2C library to read the weight from the load cell and display it on the LCD.

## Hardware Requirements
- HX711 load cell amplifier
- I2C LCD display
- Load cell sensor
- Arduino board

## Pin Connections
- Connect the DOUT pin of the HX711 to pin 4 of the Arduino board
- Connect the SCK pin of the HX711 to pin 5 of the Arduino board
- Connect the SDA and SCL pins of the I2C LCD display to the respective SDA and SCL pins of the Arduino board

## Calibration
The scale must be calibrated with known weights before use. The value of `scale.set_scale(193.15)` is obtained by calibrating the scale. This value is used to convert the raw data from the load cell to the weight in grams. Adjust this value as necessary.

## Usage
1. Upload the code to the Arduino board
2. Open the serial monitor to check the weight readings
3. The LCD will display the weight in grams and "SISA PAKAN"
4. The Scale will be powered down after 2 seconds and powered up again for next reading
5. Make sure there is no weight on the scale before running the code

## Note
- The `scale.tare(50)` function is used to reset the scale to zero. The argument of this function is the number of readings to take while taring the scale.
- The `scale.get_units(25)` function is used to get the weight from the scale. The argument of this function is the number of readings to take while getting the weight.
- The `lcd.backlight()` function is used to turn on the backlight of the LCD.
- The `scale.power_down()` and `scale.power_up()` functions are used to save power and get accurate readings.
