int BUTTON = 4;
int LEDG = 12;

void setup() {
  // put your setup code here, to run once:
 pinMode(BUTTON,INPUT);
 pinMode(LEDG,OUTPUT);
}

void loop() {
  if(digitalRead(BUTTON) == HIGH){
    digitalWrite(LEDG, HIGH);
  }
  else{
    digitalWrite(LEDG, LOW);
  }
}
