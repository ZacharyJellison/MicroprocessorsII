//Variable Declerations
boolean toggle = 0;
boolean safety = 0;

const int greenArrow = 10;
const int green = 11;
const int yellow = 12;
const int red = 13;
const int button = 2;
const int buzzer = 8;


void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(greenArrow, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(button, INPUT);
}

//Needed for Interrupt function to work
void safetyChange(){
  safety = 1;
}

//Buzzer Sound and blink
void buzzBlink(int ledPin, bool flash = true, bool buzz = true){
  if (flash == false){
    digitalWrite(ledPin, HIGH);
  }
  if (buzz == true) {
    digitalWrite(buzzer, HIGH);
  }
  if (flash == true) {
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
  if (flash == true) {
    digitalWrite(ledPin, HIGH);
  }
  delay(1000);  
  if (flash == true) {
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
  if (buzz == true) {
    digitalWrite(buzzer, LOW);
  }
  if (flash == false){
    digitalWrite(ledPin, LOW);
  }
}

void loop() {
  toggle = digitalRead(button);         //Set Button read to toggle
//Interrupt
  attachInterrupt(digitalPinToInterrupt(button), safetyChange, RISING);

//Blinking red waiting for Button Press to Begin
  while(safety == 0){

  //Blink
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(red, LOW);
    delay(1000); 
  }

//Signal Change Loop
  //Green Arrow
    digitalWrite(greenArrow, HIGH);
    delay(2000);
    buzzBlink(greenArrow);
  //Green Signal
    digitalWrite(green, HIGH);
    delay(9000);
    buzzBlink(green);
  //Yellow Signal
    buzzBlink(yellow, false);
  //Red Signal
    digitalWrite(red, HIGH);
    delay(17000);
    buzzBlink(red);
}
