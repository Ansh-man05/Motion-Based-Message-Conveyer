#include <LiquidCrystal.h>
#include <RCSwitch.h>


LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

RCSwitch mySwitch = RCSwitch();


int value;
int Buzzer = 13;



void setup(){
  Serial.begin(9600);
  mySwitch.enableReceive(0); 
  delay(100);

  lcd.begin(16, 2);
  lcd.print("MESSAGE");
  lcd.setCursor(7,1);
  lcd.print("CONVEYER");
  delay(5000);
  lcd.clear();
  

  
  

  pinMode(Buzzer,OUTPUT);
}


void loop(){
  if (mySwitch.available()) {   
    value = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    
  }
  
  lcd.setCursor(0,0);
  lcd.clear();
  
    
  if     ( value == 1111){digitalWrite(Buzzer,HIGH); delay(200);lcd.print("NEED ASSISTANCE ");digitalWrite(Buzzer,LOW);delay(200);}
  else if( value == 2222){digitalWrite(Buzzer,HIGH); delay(200);lcd.print("I NEED WATER  ");digitalWrite(Buzzer,LOW);delay(200);}
  else if( value == 3333){digitalWrite(Buzzer,HIGH); delay(200);lcd.print("I AM HUNGRY   ");digitalWrite(Buzzer,LOW);delay(200);}
  else if( value == 4444){digitalWrite(Buzzer,HIGH); delay(50);lcd.print("EMERGENCY  ");digitalWrite(Buzzer,LOW);delay(50);}
  else if( value == 9999){lcd.print(" ALL GOOD ");digitalWrite(Buzzer,LOW);}
  else   (digitalWrite(Buzzer,LOW));
}
