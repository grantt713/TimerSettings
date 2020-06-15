/*
 * This is test code to learn about millis() and display the running time on the LCD screen
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // sets the LCD address to 0x27 for a 16 char and 2 line display

int time;
int OSEC;
int SEC, MIN, HR;


void setup() {
Serial.begin(9600);
lcd.init(); // initialize the lcd
lcd.backlight(); // open the backlight
}

void loop() {
 
 OSEC = millis()/1000UL;
 HR = OSEC / 3600UL;
 MIN = OSEC % 3600UL / 60UL;
 SEC = OSEC % 3600UL % 60UL;

 unsigned long OTIME[] = {HR, MIN, SEC};
 
 Serial.print("Time- "); Serial.print(OTIME[0]);Serial.print(" : ");Serial.print(OTIME[1]);Serial.print(" : "); Serial.println(OTIME[2]);


 lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
 lcd.print("Timer's Time");  // Put message on LCD screen

 lcd.setCursor(0, 1);       // cursor on column 2, line 1

 if((HR <= 9) && (MIN <= 9) && (SEC <= 9)){       // 000
 lcd.print("0");    lcd.print(HR);   lcd.print(":0");   lcd.print(MIN);   lcd.print(":0");   lcd.print(SEC);
 }
 else if((HR <= 9) && (MIN <= 9) && (SEC > 9)){   // 001
 lcd.print("0");    lcd.print(HR);   lcd.print(":0");   lcd.print(MIN);   lcd.print(":");   lcd.print(SEC);
 }
 else if((HR <= 9) && (MIN > 9) && (SEC <= 9)){   // 010
  lcd.print("0");lcd.print(HR);   lcd.print(":");   lcd.print(MIN);   lcd.print(":");   lcd.print(SEC);
 }
 else if((HR <= 9) && (MIN > 9) && (SEC > 9)){   // 011
  lcd.print("0");lcd.print(HR);   lcd.print(":");   lcd.print(MIN);   lcd.print(":");   lcd.print(SEC);
 }
  else if((HR > 9) && (MIN <= 9) && (SEC <= 9)){   // 100
  lcd.print(HR);   lcd.print(":0");   lcd.print(MIN);   lcd.print(":0");   lcd.print(SEC);
 }
  else if((HR > 9) && (MIN <= 9) && (SEC > 9)){   // 101
  lcd.print(HR);   lcd.print(":0");   lcd.print(MIN);   lcd.print(":");   lcd.print(SEC);
 }
  else if((HR > 9) && (MIN > 9) && (SEC <= 9)){   // 110
  lcd.print(HR);   lcd.print(":");   lcd.print(MIN);   lcd.print(":0");   lcd.print(SEC);
 }
 else{                                             // 111
  lcd.print(HR);   lcd.print(" : ");   lcd.print(MIN);   lcd.print(" : ");   lcd.print(SEC);
 }
 

 delay(1000);

}
