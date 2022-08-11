#include <RCSwitch.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <EEPROM.h>

RCSwitch mySwitch = RCSwitch();


int LED1 = 8;
int LED2 = 9;
int LED3 = 10;
int LED4 = 11;

float val1;
float val2;
float valX;
float valY;

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
   
  mySwitch.enableTransmit(4);
  
  pinMode(LED1 , OUTPUT);
  pinMode(LED2 , OUTPUT);
  pinMode(LED3 , OUTPUT);
  pinMode(LED4 , OUTPUT);

  
  val1 = 0;
  val2 = 0;
  EEPROM.write(0, val1);
  EEPROM.write(1, val2);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }


  
  Serial.println("MPU6050 Found!");

 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


   valX = a.acceleration.x;
   valY = a.acceleration.y;

   if      ( EEPROM.read(0) + 8 < valX ) { digitalWrite(LED2,HIGH); mySwitch.send(1111, 24);}
   else if ( EEPROM.read(0) - 8 > valX ) { digitalWrite(LED1,HIGH); mySwitch.send(2222, 24);}
   else if ( EEPROM.read(1) + 8 < valY ) { digitalWrite(LED3,HIGH); mySwitch.send(3333, 24);}
   else if ( EEPROM.read(1) - 8 > valY ) { digitalWrite(LED4,HIGH); mySwitch.send(4444, 24);}
   
   else                                  { digitalWrite(LED1,LOW); 
                                          digitalWrite(LED2,LOW);
                                          digitalWrite(LED3,LOW);
                                          digitalWrite(LED4,LOW);  
                                          
                                         mySwitch.send(9999, 24); }                                        
                                         

  
    delay(300);
  

}
