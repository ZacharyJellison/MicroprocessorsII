//www.elegoo.com
//2016.12.09


#include <Wire.h>



//testing getting output from joystick on the arduino
int VRx = A0;
int VRy = A1;
int buzz = 4;

int xPosition = 0;
int yPosition = 0;
int mapX = 0;
int mapY = 0;

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(buzz, OUTPUT);
  checkSettings();
}

void checkSettings() {
  Serial.println();
}

void joystick() {

  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);

  if(yPosition >= 800 && yPosition <= 1023){
    Serial.print("w");
    delay(100);
  } else if(xPosition >= 800 && xPosition <= 1023){
    Serial.print("a");
    delay(100);
  } else if(yPosition >= 0 && yPosition <= 300){
    Serial.print("s");
    delay(100);
  } else if(xPosition >= 0 && xPosition <= 300){
    Serial.print("d");
    delay(100);
  }
}

void loop() {
  joystick();
}
