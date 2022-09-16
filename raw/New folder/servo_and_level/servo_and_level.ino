#include "config.h"
String dataIn;
String dt[8];
int i;
boolean parsing=false; 


void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  dataIn="";
   //servo attach to pin D3
  ser.attach(2);

  // wifi connection begin
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  mqtt.subscribe(&servo);
}
void loop() {
  
  //connect to mqtt service
  
if(mySerial.available()>0) {// check serial
    char inChar = (char)mySerial.read();//variable inchar = hasil pembacaan serial
    dataIn += inChar; // dataIn + data inchar
    if (inChar == '\n') {
    parsing = true;
  }// jika charakter yag terbaca = \n maka melakukan parsing
}
 
if(parsing){
    parsingData();
    parsing=false;
    dataIn="";
  }
  //millis 

  //delay(20);
}

void parsingData(){
int j=0;
 
//inisialisasi variabel, (reset isi variabel)
dt[j]="";
//proses parsing data
for(i=1;i<dataIn.length();i++){
//pengecekan tiap karakter dengan karakter (#) dan (,)
if ((dataIn[i] == '#') || (dataIn[i] == ','))
{
j++;
dt[j]="";       //inisialisasi variabel array dt[j]
}
else
{

dt[j] = dt[j] + dataIn[i];
}
}
//kirim data hasil parsing
int nilaiLC = dt[0].toInt();  
//nilaiLC=(nilaiLC)+(20);
Serial.println (nilaiLC); 

MQTT_connect();

loadcell.publish(nilaiLC);
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

    //reading sensor
    int sValue = analogRead(A0);
    byte mValue = map(sValue, 400, 1024, 100, 50);
    
    //tweaking some inconsistan reading value
    if (mValue > 100) {
      mValue = 100;
    }
    
    //publising data
    level.publish(mValue);
    previousTime = currentTime;
  }
}
