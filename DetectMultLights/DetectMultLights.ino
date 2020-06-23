/*
 * This is test code to learn about millis() and display the running time on the LCD screen
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

int DONE = 0, DONE2 = 0;

int BUTT = 2;
int BUTT_READ;
int BUTT2 = 3; 
int BUTT_READ2;


int LDR_IN = A0;
int LDR_VAL;
int LDR_SET;

int LDR_IN2 = A1;
int LDR_VAL2;
int LDR_SET2;

      /**************************   Function to place zeros properly   *********************************/
int DisplayFunction(int hours, int minutes, int seconds){
       if((hours <= 9) && (minutes <= 9) && (seconds <= 9)){       // 000
       lcd.print("0");    lcd.print(hours);   lcd.print(":0");   lcd.print(minutes);   lcd.print(":0");   lcd.print(seconds);
       }
       else if((hours <= 9) && (minutes <= 9) && (seconds > 9)){   // 001
       lcd.print("0");    lcd.print(hours);   lcd.print(":0");   lcd.print(minutes);   lcd.print(":");   lcd.print(seconds);
       }
       else if((hours <= 9) && (minutes > 9) && (seconds <= 9)){   // 010
        lcd.print("0");lcd.print(hours);   lcd.print(":");   lcd.print(minutes);   lcd.print(":");   lcd.print(seconds);
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
        lcd2.print("0");lcd2.print(hours);   lcd2.print(":");   lcd2.print(minutes);   lcd2.print(":");   lcd2.print(seconds);
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

 BUTT_READ = digitalRead(BUTT);

 
// Serial.print("Time- "); Serial.print(OTIME[0]);Serial.print(" : ");Serial.print(OTIME[1]);Serial.print(" : "); Serial.println(OTIME[2]);


 LDR_VAL = analogRead(LDR_IN);
 Serial.println(DONE);


 if(DONE == 0){
       lcd.clear();
      
       lcd.setCursor(0, 0);
       lcd.print("Turn Light OFF");
      
       lcd.setCursor(0, 1);
       lcd.print("Button to Cont");
      
       LDR_SET = analogRead(LDR_IN);
        
       if (BUTT_READ == HIGH){
           DONE = 1;
        }
 }

 if((DONE == 1) && (LDR_VAL <= (LDR_SET + 150))){
      
       lcd.clear();              // clear screen
            
       lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd.print("Timer's Time");  // Put message on LCD screen

       lcd.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction(HR,MIN,SEC);  

       if (BUTT_READ == HIGH){
            DONE = 0;
       }
              
 }

 else if(LDR_VAL >= (LDR_SET +150)){



       static int OSEC_ON = OSEC;
       
       HR_ON = (OSEC - OSEC_ON) / 3600UL;
       MIN_ON = (OSEC - OSEC_ON) % 3600UL / 60UL;
       SEC_ON = (OSEC - OSEC_ON) % 3600UL % 60UL;
  
       lcd.clear();              // clear screen
  
       lcd.setCursor(1, 0);       // set the cursor to column 2, line 0
       lcd.print("Light Detected");  // Put message on LCD screen

       lcd.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction(HR_ON,MIN_ON,SEC_ON);

       DONE = 2;

         if (BUTT_READ == HIGH){
          DONE = 0;
         }

    //   Serial.print("Time- "); Serial.print(HR_ON);Serial.print(" : ");Serial.print(MIN_ON);Serial.print(" : "); Serial.println(SEC_ON);

       
 }

 if (DONE == 2){
      SEC_FIN = SEC_ON;
      MIN_FIN = MIN_ON;
      HR_FIN = HR_FIN;

       lcd.clear();              // clear screen
                  
      lcd.setCursor(3, 0);                  // set the cursor to column 2, line 0
      lcd.print("Final Time");              // Put message on LCD screen
                
      lcd.setCursor(4, 1);                  // cursor on column 4, line 1
      DisplayFunction(HR_FIN,MIN_FIN,SEC_FIN);

      delay(1000);                   // delay is just to make the screen not glitchy
      
      DONE = 3;
   }

 if(DONE == 3){
      if (BUTT_READ == HIGH){
          DONE = 0;
      }
 }



// *************************** Second Display **************************************



 HR2 = OSEC / 3600UL;
 MIN2 = OSEC % 3600UL / 60UL;
 SEC2 = OSEC % 3600UL % 60UL;

 BUTT_READ2 = digitalRead(BUTT2);

 
// Serial.print("Time- "); Serial.print(OTIME[0]);Serial.print(" : ");Serial.print(OTIME[1]);Serial.print(" : "); Serial.println(OTIME[2]);


 LDR_VAL2 = analogRead(LDR_IN2);
       // Serial.println(LDR_VAL2);
      
 if(DONE2 == 0){
        lcd2.clear();
      
        lcd2.setCursor(0, 0);
        lcd2.print("Turn Light OFF");
      
        lcd2.setCursor(0, 1);
        lcd2.print("Button to Cont");
      
        LDR_SET2 = analogRead(LDR_IN2);
        
        if (BUTT_READ2 == HIGH){
              DONE2 = 1;
  }
 }

 if((DONE2 == 1) && (LDR_VAL2 <= (LDR_SET2 + 150))){
      
       lcd2.clear();              // clear screen
            
       lcd2.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd2.print("Timer's Time");  // Put message on LCD screen

       lcd2.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction2(HR2,MIN2,SEC2);   

       if (BUTT_READ == HIGH){
            DONE = 0;
       }
              
 }

 else if(LDR_VAL2 >= (LDR_SET2 + 150)){

       static int OSEC_ON2 = OSEC;
       
       HR_ON2 = (OSEC - OSEC_ON2) / 3600UL;
       MIN_ON2 = (OSEC - OSEC_ON2) % 3600UL / 60UL;
       SEC_ON2 = (OSEC - OSEC_ON2) % 3600UL % 60UL;
  
       lcd2.clear();              // clear screen
  
       lcd2.setCursor(1, 0);       // set the cursor to column 2, line 0
       lcd2.print("Light Detected");  // Put message on LCD screen
     
       lcd2.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction2(HR_ON2,MIN_ON2,SEC_ON2);

       DONE2 = 2;

       if (BUTT_READ2 == HIGH){
          DONE2 = 0;
       }

    //   Serial.print("Time- "); Serial.print(HR_ON);Serial.print(" : ");Serial.print(MIN_ON);Serial.print(" : "); Serial.println(SEC_ON);

       
 }

 if(DONE2 == 2){
      SEC_FIN2 = SEC_ON2;
      MIN_FIN2 = MIN_ON2;
      HR_FIN2 = HR_FIN2;

       lcd2.clear();              // clear screen
                  
      lcd2.setCursor(3, 0);                  // set the cursor to column 2, line 0
      lcd2.print("Final Time");              // Put message on LCD screen
                                    
      lcd2.setCursor(4, 1);                  // cursor on column 4, line 1
      DisplayFunction2(HR_FIN2,MIN_FIN2,SEC_FIN2);

      delay(1000);                   // delay is just to make the screen not glitchy

      DONE2 = 3;
   }

 if(DONE2 == 3){
      if (BUTT_READ2 == HIGH){
          DONE2 = 0;
      }
 }
   

delay(1000);
     
}
