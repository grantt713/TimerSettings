#include <LiquidCrystal.h>


bool teststate;
bool teststart;
unsigned long previousMillis = 0;



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




void timeformatandprint(unsigned long inputseconds, int x, int y) {      

      int seconds;
      int minutes;
      int hours;
      
      if (inputseconds >= 59) {
      seconds = (inputseconds % 60);
      }
      else { 
        seconds = inputseconds;
      }
      
      if (inputseconds >= 3599) {
         minutes = ((inputseconds % 3600)/60);
      }
      else if (inputseconds > 59) {
         minutes = (inputseconds / 60);
      }
      else {
         minutes = 0;
      }
      hours = (inputseconds / 3600);
      
      
      lcd.setCursor(x, y);
      if (hours < 10) {
        lcd.print("0");
        lcd.print(hours);
      }
      else {
      lcd.print(hours);
      }
      lcd.print(":");
      if (minutes < 10) {
        lcd.print("0");
        lcd.print(minutes);
      }
      else {
      lcd.print(minutes);
      }
      lcd.print(":");

      if (seconds < 10) {
        lcd.print("0");
        lcd.print(seconds);
      }
      else {
      lcd.print(seconds);
      }  
}









void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
//    Serial.begin(9600);
}

void loop() {

  
   
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
//  lcd.print(millis()/1000);

  
  unsigned long totaltimeElapsed = (millis() / 1000);
  timeformatandprint(totaltimeElapsed, 0, 0);




  lcd.setCursor(0, 1);
  // print the number of seconds since reset:

  int farts = analogRead(A5);
  unsigned long currentMillis = millis();

  if (farts > 400 && teststart == LOW) {
    previousMillis = currentMillis;
    lcd.setCursor(0, 1);
    
    teststart = HIGH;
  }
  
  Serial.println(farts);
  if (farts <= 400 && teststate == LOW  && teststart == HIGH) {
      lcd.setCursor(0, 1);
      lcd.print("        ");
      lcd.setCursor(0, 1);
      unsigned long timeElapsed = ((currentMillis - previousMillis)/1000);
//      unsigned long timeElapsed = 3660;       ----------------diagnostic-----------------
      timeformatandprint(timeElapsed, 0, 1);
      teststate = HIGH;
  }
}
