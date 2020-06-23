#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // sets the LCD address to 0x27 for a 16 char and 2 line display
LiquidCrystal_I2C lcd2(0x26, 16, 2);

int LDR_IN = A0;
int LDR_VAL;

int LDR_IN2 = A1;
int LDR_VAL2;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.init(); // initialize the lcd
lcd.backlight(); // open the backlight

lcd2.init(); // initialize the lcd
lcd2.backlight(); // open the backlight

pinMode(LDR_IN, INPUT);
pinMode(LDR_IN2, INPUT);
}



void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(2, 0);       // set the cursor to column 2, line 0
  lcd.print("Hello");

  lcd2.setCursor(2,0);
  lcd2.print("Hey");

  LDR_VAL = analogRead(LDR_IN);
  LDR_VAL2 = analogRead(LDR_IN2);

  Serial.print("LD1: ");  Serial.println(LDR_VAL);
  Serial.print("LDR2: ");  Serial.println(LDR_VAL2);

  delay(2000);

}
