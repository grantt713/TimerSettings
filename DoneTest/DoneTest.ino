#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // sets the LCD address to 0x27 for a 16 char and 2 line display
LiquidCrystal_I2C lcd2(0x26, 16, 2);

int time;
int OSEC;
int SEC, MIN, HR;
int SEC_ON, MIN_ON, HR_ON;
int SEC_FIN, MIN_FIN, HR_FIN;

int SEC2, MIN2, HR2;
int SEC_ON2, MIN_ON2, HR_ON2;
int SEC_FIN2, MIN_FIN2, HR_FIN2;

int OSEC_ON;

int DONE = 0, DONE2 = 0;

int BUTT = 2;
boolean BUTT_READ;
int BUTT2 = 3; 
boolean BUTT_READ2;


int LDR_IN = A0;
int LDR_VAL;
int LDR_SET;

int LDR_IN2 = A1;
int LDR_VAL2;
int LDR_SET2;

/*******************************************/
boolean Debounce1(boolean State){
  boolean StateNow = digitalRead(BUTT);
  if(State!=StateNow){
    delay(1000);
    StateNow = digitalRead(BUTT);
  }
  return StateNow;
}
/******************************************************/


void setup() {
    Serial.begin(9600);
    lcd.init(); // initialize the lcd
    lcd.backlight(); // open the backlight
    
    lcd2.init(); // initialize the lcd
    lcd2.backlight(); // open the backlight
    
    pinMode(LDR_IN, INPUT);
    pinMode(LDR_IN2, INPUT);
    
    pinMode(BUTT, INPUT);
    pinMode(BUTT2, INPUT);

}



void loop() {
  // put your main code here, to run repeatedly:


  if(DONE==0){
      BUTT_READ = digitalRead(BUTT); 
      BUTT_READ = Debounce1(BUTT_READ);
      if(BUTT_READ == HIGH){
        delay(500);
        BUTT_READ = digitalRead(BUTT); 
        BUTT_READ = Debounce1(BUTT_READ);
        if(BUTT_READ==0){
          DONE = 1;
        }
      }
      Serial.print(DONE);
      Serial.println("Alright");

  }


  if(DONE==1){
      BUTT_READ = digitalRead(BUTT); 
      BUTT_READ = Debounce1(BUTT_READ);
      if(BUTT_READ == HIGH){
        delay(500);
        BUTT_READ = digitalRead(BUTT); 
        BUTT_READ = Debounce1(BUTT_READ);
        if(BUTT_READ==0){
            DONE = 2;
        }
      }
      Serial.print(DONE);
      Serial.println("Good Deal");

  }

    if(DONE==2){
      BUTT_READ = digitalRead(BUTT); 
      BUTT_READ = Debounce1(BUTT_READ);
      if(BUTT_READ == HIGH){
        delay(500);
        BUTT_READ = digitalRead(BUTT); 
        BUTT_READ = Debounce1(BUTT_READ);
        if(BUTT_READ==0){
            DONE = 0;
        }
      }
      Serial.print(DONE);
      Serial.println("Back to Start");
    }
delay(500);
}
