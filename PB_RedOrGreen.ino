// code is written to test offbrand nanos

int BUTTON = 3;
int LEDG = 4; 
int LEDR = 5;

void setup() {
  
  pinMode(LEDG,OUTPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(BUTTON,INPUT);
  

}

void loop() {
  if(digitalRead(BUTTON) == HIGH){
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDR, LOW);
  }
  else{
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
  }

}
