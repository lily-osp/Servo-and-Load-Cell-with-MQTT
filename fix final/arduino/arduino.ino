#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;  

LiquidCrystal_I2C lcd(0x27, 16, 2);
HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Pastikan Tidak Ada Beban");
  lcd.init();
  lcd.backlight();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(193.15);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(50);				        // reset the scale to 0
  Serial.println("Silahkan Untuk Menimbang");
}

void loop() {
  Serial.print("Berat");
  float berat= scale.get_units(25);
  if(berat<=0.1)
  {
    berat=0.0;
  }
  Serial.println(berat,1);
  if(berat<1000)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SISA PAKAN");
  lcd.setCursor(0, 1);
  lcd.print("Berat= ");
  lcd.print(berat,1);
  lcd.print(" gr");
  }
  if(berat>=1000)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SISA PAKAN");
  float hasil=berat/1000;
  lcd.setCursor(0, 1);
  lcd.print("Berat= ");
  lcd.print(hasil);
  lcd.print(" gr");
  }
  scale.power_down();
  delay(2000);
  scale.power_up();
}
#include "HX711.h"

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

const int LOADCELL_DOUT_PIN = 4;

const int LOADCELL_SCK_PIN = 5;  

// Create an instance of the I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Create an instance of the HX711 library

HX711 scale;

void setup() {

  // Start the serial communication

  Serial.begin(9600);

  // Print a message to ensure that there is no weight on the scale

  Serial.println("Make sure there is no weight on the scale");

  // Initialize the LCD

  lcd.init();

  // Turn on the backlight of the LCD

  lcd.backlight();

  // Initialize the HX711 with the DOUT and SCK pin numbers

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Set the scale factor for the load cell, obtained by calibrating with known weights

  scale.set_scale(193.15);

  // Tare the scale to reset it to zero

  scale.tare(50);

  // Print a message to indicate that the scale is ready for use

  Serial.println("You can now start weighing");

}

void loop() {

  // Print the word "Weight" to the serial monitor

  Serial.print("Weight: ");

  // Get the weight from the scale, with 25 readings

  float weight = scale.get_units(25);

  // If the weight is less than or equal to 0.1, set it to 0

  if(weight <= 0.1) {

    weight = 0.0;

  }

  // Print the weight to the serial monitor

  Serial.println(weight, 1);

  

  // Clear the LCD

  lcd.clear();

  // Set the cursor to the first column of the first row

  lcd.setCursor(0, 0);

  // Print the title "SISA PAKAN"

  lcd.print("SISA PAKAN");

  // Set the cursor to the first column of the second row

  lcd.setCursor(0, 1);

  

  // Check if the weight is less than 1000 grams

  if(weight < 1000) {

    // Print the weight in grams

    lcd.print("Weight: ");

    lcd.print(weight, 1);

    lcd.print(" gr");

  } else {

    // If the weight is greater than or equal to 1000 grams, convert it to kilograms

    float result = weight / 1000;

    // Print the weight in kilograms

    lcd.print("Weight: ");

    lcd.print(result);

    lcd.print(" kg");

  }

  

  // Power down the scale to save power and improve accuracy

  scale.power_down();

  // Wait for 2 seconds

  delay(2000);

  // Power up the scale for the next reading

  scale.power_up();

}
