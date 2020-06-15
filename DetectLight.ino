/*
 * This is test code to learn about millis() and display the running time on the LCD screen
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // sets the LCD address to 0x27 for a 16 char and 2 line display

int time;
int OSEC;
int SEC, MIN, HR;
int SEC_ON, MIN_ON, HR_ON;
int SEC_FIN, MIN_FIN, HR_FIN;
int DONE = 0;


int LDR_IN = A1;
int LDR_VAL;

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
 /************************************************************************************************/
 



/*************************************   SETUP   **********************************************/
void setup() {
Serial.begin(9600);
lcd.init(); // initialize the lcd
lcd.backlight(); // open the backlight

pinMode(LDR_IN, INPUT);
}
/***************************************************************************/





/**********************************   Main Loop   *********************************************************/
void loop() {
 
 OSEC = millis()/1000UL;
 HR = OSEC / 3600UL;
 MIN = OSEC % 3600UL / 60UL;
 SEC = OSEC % 3600UL % 60UL;

 unsigned long OTIME[] = {HR, MIN, SEC};
 
// Serial.print("Time- "); Serial.print(OTIME[0]);Serial.print(" : ");Serial.print(OTIME[1]);Serial.print(" : "); Serial.println(OTIME[2]);


 LDR_VAL = analogRead(LDR_IN);
 // Serial.println(LDR_VAL);
 

 if((LDR_VAL < 475) && (DONE == 0)){
      
       lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd.print("                 ");  // Resets LCD screen
            
       lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd.print("Timer's Time");  // Put message on LCD screen
              
       lcd.setCursor(0, 1);       // cursor on column 4, line 1
       lcd.print("                          ");  // Resets LCD screen

       lcd.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction(HR,MIN,SEC);      
              
 }

 else if(LDR_VAL >= 475){

       static int HR2 = HR;
       static int MIN2 = MIN;
       static int SEC2 = SEC;
       
       HR_ON = HR - HR2;
       MIN_ON = MIN - MIN2;
       SEC_ON = SEC - SEC2;

       lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
       lcd.print("                   ");  // Resets LCD screen
  
       lcd.setCursor(1, 0);       // set the cursor to column 2, line 0
       lcd.print("Light Detected");  // Put message on LCD screen
      
       lcd.setCursor(0, 1);       // cursor on column 4, line 1
       lcd.print("                        ");  // Resets LCD screen

       lcd.setCursor(4, 1);       // cursor on column 4, line 1
       DisplayFunction(HR_ON,MIN_ON,SEC_ON);

       DONE = 1;

    //   Serial.print("Time- "); Serial.print(HR_ON);Serial.print(" : ");Serial.print(MIN_ON);Serial.print(" : "); Serial.println(SEC_ON);

       
 }

 else{
      SEC_FIN = SEC_ON;
      MIN_FIN = MIN_ON;
      HR_FIN = HR_FIN;

      lcd.setCursor(0, 0);                  // set the cursor to column 2, line 0
      lcd.print("                        ");      // Resets LCD screen
                  
      lcd.setCursor(3, 0);                  // set the cursor to column 2, line 0
      lcd.print("Final Time");              // Put message on LCD screen
                      
      lcd.setCursor(0, 1);        // cursor on column 4, line 1
      lcd.print("                     ");   // Resets LCD screen
                
      lcd.setCursor(4, 1);                  // cursor on column 4, line 1
      DisplayFunction(HR_FIN,MIN_FIN,SEC_FIN);

      delay(10000000000);                   // delay is just to make the screen not glitchy
   }

delay(1000);
     
}
