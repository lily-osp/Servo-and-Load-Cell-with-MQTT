# HX711_ADC
This is an Arduino library for the HX711 24-Bit Analog-to-Digital Converter for Weight Scales. This library has been created by Olav Kallhovd in September 2017.

## Hardware Requirements
- HX711 load cell amplifier
- Arduino board

## Pin Connections
- Connect the DOUT pin of the HX711 to pin 4 of the Arduino board
- Connect the SCK pin of the HX711 to pin 5 of the Arduino board

## Calibration
This code includes an example of how to calibrate the load cell and store the calibration value in EEPROM. The code also shows how to change the value manually. 
To implement calibration in your project sketch, the simplified procedure is as follows:

1. Call `LoadCell.tare()` to set the tare offset.
2. Place a known mass on the load cell.
3. Call `LoadCell.refreshDataSet()` to refresh the data set.
4. Call `LoadCell.getNewCalibration(known_mass)` to get the new calibration value.

## Usage
1. Upload the code to the Arduino board
2. Open the serial monitor to check the weight readings
3. Send 't' from serial monitor to set the tare offset
4. Send 'r' from serial monitor to start the calibration process
5. Send 'c' from serial monitor to manually change the calibration value
6. Make sure there is no weight on the load cell before running the code

## Note
- The `LoadCell.setReverseOutput()` function is used to turn a negative output value to positive.
- The `LoadCell.start(stabilizingtime, _tare)` function is used to start the load cell with a stabilization time and tare option.
- The `LoadCell.setCalFactor(1.0)` function is used to set the calibration factor.
- The `LoadCell.update()` function is used to update the load cell.
- The `LoadCell.getData()` function is used to get the smoothed value from the dataset.
- The `LoadCell.tareNoDelay()` function is used to tare the load cell without delay.
- The `LoadCell.tare()` function is used to reset the scale to zero. The argument of this function is the number of readings to take while taring the scale.
- The `LoadCell.getData()` function is used to get the weight from the scale. The argument of this function is the number of readings to take while getting the weight.
- The `LoadCell.start()` function is used to start the HX711 and set the stabilization time and tare status.
- The `LoadCell.setCalFactor()` function is used to set the calibration factor.
- The `calibrate()` function is used to start the calibration process and get the new calibration value.
- The `changeSavedCalFactor()` function is used to change the calibration value manually, which can be stored in EEPROM.
- The `LoadCell.getData()` function is used to get the weight from the scale. The function returns the smoothed value of the dataset.
- The `Serial.available()` function is used to check if there is any command received from serial monitor.
- The `calibrate()` function is used to start the calibration procedure, where user can input a known mass and the new calibration value is calculated and can be stored in EEPROM if desired.
- The `changeSavedCalFactor()` function is used to manually edit the calibration value stored in EEPROM.
