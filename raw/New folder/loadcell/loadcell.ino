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
