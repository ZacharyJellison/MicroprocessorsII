#include <LiquidCrystal.h>
#include "Arduino.h"
#include "uRTCLib.h"

#define ENABLE 5
#define DIRA 3
#define DIRB 4

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// uRTCLib rtc;
uRTCLib rtc(0x68);

void setup() {
  Serial.begin(9600);
  delay(3000); // wait for console opening

//---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);

  URTCLIB_WIRE.begin();

  rtc.set(0, 0, 0, 0, 1, 1, 1);
  // rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time  Speed  Dir");
}

void loop() {
  rtc.refresh();

//Print Time
  lcd.setCursor(0, 1);
  lcd.print(rtc.minute());
  lcd.print(":");

  if(rtc.second() < 10){
    lcd.print("0");
    lcd.print(rtc.second());
  }
  else{
    lcd.print(rtc.second());
  }

//Put motor into motion
  if(rtc.second() <= 30){
  //On 0 - 30 seconds
    analogWrite(ENABLE,255);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
  }
  else{
  //Off 31 = 60 seconds
    analogWrite(ENABLE,LOW);
    digitalWrite(DIRA,LOW);
    digitalWrite(DIRB,LOW);
  }

//Print Speed
  lcd.setCursor(6, 1);
  if(digitalRead(DIRA) == HIGH){
    lcd.print("FULL");
  }
  else if(analogRead(DIRB) == HIGH){
    lcd.print("FULL");
  }
  else{
  lcd.print("  0     ");
  }

//Print Direction
  lcd.setCursor(13, 1);
  if(digitalRead(DIRA) == HIGH){
    lcd.print(" C ");
  }
  else if (digitalRead(DIRB) == HIGH){
    lcd.print("CC ");
  }
  else{
    lcd.print("N/A");
  }

  delay(1000);
}
