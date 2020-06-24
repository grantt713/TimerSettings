/*
 * This is code to perform 3 timer setting checks with one arduino nano. It implements
 * 4 phases or screens. 
 * 
 * 1. Instructions
 * 2. Running/Overall Time
 * 3. Light Detected
 * 4. Final Time device was on
 * 
 * All three timer settings should be completely isolated and should be capable of being
 * reset in the middle of a test without disturbing the other timers.
 * 
 * Original Coder: Grant Turner
 * Date Written: 6/24/20
 * 
 */

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

int OSEC_ON, OSEC_ON2;

int DONE = 0, DONE2 = 0;

int BUTT = 2;
boolean BUTT_READ;
int BUTT2 = 3; 
boolean BUTT_READ2;

int RESET=0, RESET_CHECK=0;
int RESET2=0, RESET_CHECK2=0;

int LDR_IN = A0;
int LDR_VAL;
int LDR_SET=10000;

int LDR_IN2 = A1;
int LDR_VAL2;
int LDR_SET2=10000;

      /**************************   Function to place zeros properly   *********************************/
int DisplayFunction(int hours, int minutes, int seconds){
       if((hours <= 9) && (minutes <= 9) && (seconds <= 9)){       // 000
       lcd.print("0");    lcd.print(hours);   lcd.print(":0");   lcd.print(minutes);   lcd.print(":0");   lcd.print(seconds);
       }
       else if((hours <= 9) && (minutes <= 9) && (seconds > 9)){   // 001
       lcd.print("0");    lcd.print(hours);   lcd.print(":0");   lcd.print(minutes);   lcd.print(":");   lcd.print(seconds);
       }
       else if((hours <= 9) && (minutes > 9) && (seconds <= 9)){   // 010
        lcd.print("0");lcd.print(hours);   lcd.print(":");   lcd.print(minutes);   lcd.print(":0");   lcd.print(seconds);
       }
       else if((hours <= 9) && (minutes > 9) && (seconds > 9)){   // 011
        lcd.print("0");lcd.print(hours);   lcd.print(":");   lcd.print(minutes);   lcd.print(":");   lcd.print(seconds);
       }
        else if((hours > 9) && (minutes <= 9) && (seconds <= 9)){   // 100
        lcd.print(hours);   lcd.print(":0");   lcd.print(minutes);   lcd.print(":0");   lcd.print(seconds);
       }
        else if((hours > 9) && (minutes <= 9) && (seconds > 9)){   // 101
        lcd.print(hours);   lcd.print(":0");   lcd.print(minutes);   lcd.print(":");   lcd.print(seconds);
       }
        else if((hours > 9) && (minutes > 9) && (seconds <= 9)){   // 110
        lcd.print(hours);   lcd.print(":");   lcd.print(minutes);   lcd.print(":0");   lcd.print(seconds);
       }
       else{                                             // 111
        lcd.print(hours);   lcd.print(" : ");   lcd.print(minutes);   lcd.print(" : ");   lcd.print(seconds);
       }
  }


  int DisplayFunction2(int hours, int minutes, int seconds){
       if((hours <= 9) && (minutes <= 9) && (seconds <= 9)){       // 000
       lcd2.print("0");    lcd2.print(hours);   lcd2.print(":0");   lcd2.print(minutes);   lcd2.print(":0");   lcd2.print(seconds);
       }
       else if((hours <= 9) && (minutes <= 9) && (seconds > 9)){   // 001
       lcd2.print("0");    lcd2.print(hours);   lcd2.print(":0");   lcd2.print(minutes);   lcd2.print(":");   lcd2.print(seconds);
       }
       else if((hours <= 9) && (minutes > 9) && (seconds <= 9)){   // 010
        lcd2.print("0");lcd2.print(hours);   lcd2.print(":");   lcd2.print(minutes);   lcd2.print(":0");   lcd2.print(seconds);
       }
       else if((hours <= 9) && (minutes > 9) && (seconds > 9)){   // 011
        lcd2.print("0");lcd2.print(hours);   lcd2.print(":");   lcd2.print(minutes);   lcd2.print(":");   lcd2.print(seconds);
       }
        else if((hours > 9) && (minutes <= 9) && (seconds <= 9)){   // 100
        lcd2.print(hours);   lcd2.print(":0");   lcd2.print(minutes);   lcd2.print(":0");   lcd2.print(seconds);
       }
        else if((hours > 9) && (minutes <= 9) && (seconds > 9)){   // 101
        lcd2.print(hours);   lcd2.print(":0");   lcd2.print(minutes);   lcd2.print(":");   lcd2.print(seconds);
       }
        else if((hours > 9) && (minutes > 9) && (seconds <= 9)){   // 110
        lcd2.print(hours);   lcd2.print(":");   lcd2.print(minutes);   lcd2.print(":0");   lcd2.print(seconds);
       }
       else{                                             // 111
        lcd2.print(hours);   lcd2.print(" : ");   lcd2.print(minutes);   lcd2.print(" : ");   lcd2.print(seconds);
       }
  }
 /************************************************************************************************/
 
/********************************* Functions to Debounce PBs ******************************************************/
boolean Debounce1(boolean State){
  boolean StateNow = digitalRead(BUTT);
  if(State!=StateNow){
    delay(100);
    StateNow = digitalRead(BUTT);
  }
  return StateNow;
}

boolean Debounce2(boolean State){
  boolean StateNow = digitalRead(BUTT2);
  if(State!=StateNow){
    delay(100);
    StateNow = digitalRead(BUTT2);
  }
  return StateNow;
}

/*************************************   SETUP   **********************************************/
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
/***************************************************************************/





/**********************************   Main Loop   *********************************************************/
void loop() {
 
 OSEC = millis()/1000UL;
 HR = OSEC / 3600UL;
 MIN = OSEC % 3600UL / 60UL;
 SEC = OSEC % 3600UL % 60UL;

 
// Serial.print("Time- "); Serial.print(OTIME[0]);Serial.print(" : ");Serial.print(OTIME[1]);Serial.print(" : "); Serial.println(OTIME[2]);


 LDR_VAL = analogRead(LDR_IN);
 // Serial.println(LDR_VAL);

 Serial.println(DONE);


 
// ******************* Stage 1: Introduction ************************

if((DONE==0) && (DONE2==0)){
  lcd.clear();
  lcd2.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("Make Sure Light is OFF!");
  lcd.setCursor(15, 1);
  lcd.print("- Setting Lux Baseline");

  lcd2.setCursor(2, 0);
  lcd2.print("Make Sure Light is OFF!");
  lcd2.setCursor(15, 1);
  lcd2.print("- Setting Lux Baseline");
  
  for(int i=0; i<=25; i++){
    lcd.scrollDisplayLeft();
    lcd2.scrollDisplayLeft();
    delay(600);
  }
}

//****************************************************************************************************************************
//************************************************* First Screen ***************************************************************
//****************************************************************************************************************************

  
if(DONE == 0){    
  
  LDR_SET = analogRead(LDR_IN);
  
  DONE = 1;
}


 if((LDR_VAL < (LDR_SET+100)) && (DONE == 1)){
      
       lcd.clear();
            
       lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd.print("Running Time");  // Put message on LCD screen

       lcd.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction(HR,MIN,SEC);      

       BUTT_READ = digitalRead(BUTT); 
       BUTT_READ = Debounce1(BUTT_READ);
       if(BUTT_READ == HIGH){
        delay(500);
        BUTT_READ = digitalRead(BUTT); 
        BUTT_READ = Debounce1(BUTT_READ);
        if(BUTT_READ==0){          // make sure user let go of button
          DONE = 0;
          OSEC_ON = 0;            // reset the ON timer
          RESET++;
         }
          
       }

  }


 else if((LDR_VAL >= (LDR_SET+100)) && (DONE2 != 3)){
       if((RESET>RESET_CHECK) || (RESET_CHECK==RESET)){
          OSEC_ON = OSEC;
          RESET_CHECK++;
       }
       
       
       HR_ON = (OSEC - OSEC_ON) / 3600UL;
       MIN_ON = (OSEC - OSEC_ON) % 3600UL / 60UL;
       SEC_ON = (OSEC - OSEC_ON) % 3600UL % 60UL;
  
       lcd.clear();
  
       lcd.setCursor(1, 0);       // set the cursor to column 2, line 0
       lcd.print("Light Detected");  // Put message on LCD screen
      
       lcd.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction(HR_ON,MIN_ON,SEC_ON);

       DONE = 2;


       BUTT_READ = digitalRead(BUTT); 
       BUTT_READ = Debounce1(BUTT_READ);
       if(BUTT_READ == HIGH){
        delay(500);
        BUTT_READ = digitalRead(BUTT); 
        BUTT_READ = Debounce1(BUTT_READ);
        if(BUTT_READ==0){          // make sure user let go of button
          DONE = 0;
          OSEC_ON = 0;            // reset the ON timer
          RESET++;
         }
       }

       

    //   Serial.print("Time- "); Serial.print(HR_ON);Serial.print(" : ");Serial.print(MIN_ON);Serial.print(" : "); Serial.println(SEC_ON);

       
 }

else if((LDR_VAL < (LDR_SET+100)) && (DONE == 2)){
    SEC_FIN = SEC_ON;
    MIN_FIN = MIN_ON;
    HR_FIN = HR_ON;

    lcd.clear();
                
    lcd.setCursor(3, 0);                  // set the cursor to column 2, line 0
    lcd.print("Final Time");              // Put message on LCD screen
              
    lcd.setCursor(4, 1);                  // cursor on column 4, line 1
    DisplayFunction(HR_FIN,MIN_FIN,SEC_FIN);

    DONE = 3;
 }

else if(DONE == 3){
   BUTT_READ = digitalRead(BUTT); 
   BUTT_READ = Debounce1(BUTT_READ);
   if(BUTT_READ == HIGH){
        delay(500);
        BUTT_READ = digitalRead(BUTT); 
        BUTT_READ = Debounce1(BUTT_READ);
        if(BUTT_READ==0){          // make sure user let go of button
          DONE = 0;
          OSEC_ON = 0;            // reset the ON timer
          RESET++;
         }
   }
}

// *********************************************************************************************************************
// ************************************* Second Screen *****************************************************************
// *********************************************************************************************************************

OSEC = millis()/1000UL;
 HR2 = OSEC / 3600UL;
 MIN2 = OSEC % 3600UL / 60UL;
 SEC2 = OSEC % 3600UL % 60UL;

 
// Serial.print("Time- "); Serial.print(OTIME[0]);Serial.print(" : ");Serial.print(OTIME[1]);Serial.print(" : "); Serial.println(OTIME[2]);


 LDR_VAL2 = analogRead(LDR_IN2);
 // Serial.println(LDR_VAL);

 Serial.println(DONE2);


 
if(DONE2 == 0){

  LDR_SET2 = analogRead(LDR_IN2);
  
  DONE2 = 1;
}


 if((LDR_VAL2 < (LDR_SET2+100)) && (DONE2 == 1)){
      
       lcd2.clear();
            
       lcd2.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd2.print("Running Time");  // Put message on LCD screen

       lcd2.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction2(HR,MIN,SEC);      

       BUTT_READ2 = digitalRead(BUTT2); 
       BUTT_READ2 = Debounce2(BUTT_READ2);
       if(BUTT_READ2 == HIGH){
        delay(500);
        BUTT_READ2 = digitalRead(BUTT2); 
        BUTT_READ2 = Debounce2(BUTT_READ2);
        if(BUTT_READ2==0){          // make sure user let go of button
          DONE2 = 0;
          OSEC_ON2 = 0;            // reset the ON timer
          RESET2++;
         }
          
       }

  }


 else if((LDR_VAL2 >= (LDR_SET2+100)) && (DONE2 != 3)){
       if((RESET2>RESET_CHECK2) || (RESET_CHECK2==RESET2)){
          OSEC_ON2 = OSEC;
          RESET_CHECK2++;
       }
       
       
       HR_ON2 = (OSEC - OSEC_ON2) / 3600UL;
       MIN_ON2 = (OSEC - OSEC_ON2) % 3600UL / 60UL;
       SEC_ON2 = (OSEC - OSEC_ON2) % 3600UL % 60UL;
  
       lcd2.clear();
  
       lcd2.setCursor(1, 0);       // set the cursor to column 2, line 0
       lcd2.print("Light Detected");  // Put message on LCD screen
      
       lcd2.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction2(HR_ON2,MIN_ON2,SEC_ON2);

       DONE2 = 2;


       BUTT_READ2 = digitalRead(BUTT2); 
       BUTT_READ2 = Debounce2(BUTT_READ2);
       if(BUTT_READ2 == HIGH){
        delay(500);
        BUTT_READ2 = digitalRead(BUTT2); 
        BUTT_READ2 = Debounce2(BUTT_READ2);
        if(BUTT_READ2==0){          // make sure user let go of button
          DONE2 = 0;
          OSEC_ON2 = 0;            // reset the ON timer
          RESET2++;
         }
       }

       

    //   Serial.print("Time- "); Serial.print(HR_ON);Serial.print(" : ");Serial.print(MIN_ON);Serial.print(" : "); Serial.println(SEC_ON);

       
 }

else if((LDR_VAL2 < (LDR_SET2+100)) && (DONE2 == 2)){
    SEC_FIN2 = SEC_ON2;
    MIN_FIN2 = MIN_ON2;
    HR_FIN2 = HR_ON2;

    lcd2.clear();
                
    lcd2.setCursor(3, 0);                  // set the cursor to column 2, line 0
    lcd2.print("Final Time");              // Put message on LCD screen
              
    lcd2.setCursor(4, 1);                  // cursor on column 4, line 1
    DisplayFunction2(HR_FIN2,MIN_FIN2,SEC_FIN2);

    DONE2 = 3;
 }

else if(DONE2 == 3){
   BUTT_READ2 = digitalRead(BUTT2); 
   BUTT_READ2 = Debounce2(BUTT_READ2);
   if(BUTT_READ2 == HIGH){
        delay(500);
        BUTT_READ2 = digitalRead(BUTT2); 
        BUTT_READ2 = Debounce2(BUTT_READ2);
        if(BUTT_READ2==0){          // make sure user let go of button
          DONE2 = 0;
          OSEC_ON2 = 0;            // reset the ON timer
          RESET2++;
         }
   }
}

delay(500);
     
}
