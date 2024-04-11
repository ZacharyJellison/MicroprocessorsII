#include <LiquidCrystal.h>
#include "Arduino.h"
#include "uRTCLib.h"
#include <arduinoFFT.h>

#define SAMPLES 256             // Must be a power of 2
#define SAMPLING_FREQUENCY 10000 // Hz, must be less than 10000 due to ADC
#define THRESHOLD 512
#define SAMPLE_INTERVAL 100 // Interval between samples in microseconds

#define ENABLE 5
#define DIRA 3
#define DIRB 4

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];
double finalFrequency;
double peak = 0;
int speed = 0;
int buttonPress = 0;

arduinoFFT FFT = arduinoFFT();

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// uRTCLib rtc;
uRTCLib rtc(0x68);

void buttPress(){
  if (buttonPress == 0){
    buttonPress = 1;
  }
  else if (buttonPress == 1){
    buttonPress = 0;
  }
  else{
    buttonPress = buttonPress;
  }
}

void setup() {
  Serial.begin(9600);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  attachInterrupt(digitalPinToInterrupt(2), buttPress, RISING);

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
  lcd.print("Time    Spd  Dir");
}

void loop() {
  rtc.refresh();

  //SAMPLING
  for(int i=0; i<SAMPLES; i++) {
    microseconds = micros();    //Overflows after around 70 minutes!
    vReal[i] = analogRead(A0);
    vImag[i] = 0;
    while(micros() < (microseconds + sampling_period_us)){
    }
  }

  //FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
  peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);


  peak = peak * .775;

  Serial.println(peak);

//Print Time
  lcd.setCursor(0, 1);

  if(rtc.hour() < 10){
    lcd.print("0");
    lcd.print(rtc.hour());
  }
  else{
    lcd.print(rtc.hour());
  }

  lcd.print(":");

  if(rtc.minute() < 10){
    lcd.print("0");
    lcd.print(rtc.minute());
  }
  else{
    lcd.print(rtc.minute());
  }
  
  lcd.print(":");

  if(rtc.second() < 10){
    lcd.print("0");
    lcd.print(rtc.second());
  }
  else{
    lcd.print(rtc.second());
  }


//Set Speed
  if ((peak >= 257) && (peak <= 267)){
    //Increment
    if (speed == 0){
      speed = 128;
    }
    else if (speed == 128){
      speed = 192;
    }
    else if (speed == 192){
      speed = 255;
    }
    else if (speed == 255){
      speed = 255;
    }
  }
  else if ((peak >= 430) && (peak <= 450)){
    //Decrement
    if (speed == 0){
      speed = 0;
    }
    else if (speed == 128){
      speed = 0;
    }
    else if (speed == 192){
      speed = 128;
    }
    else if (speed == 255){
      speed = 192;
    }
  }
  else{
    speed = speed;
  }


if (buttonPress == 1){
  analogWrite(ENABLE,speed);
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
}
else{
    analogWrite(ENABLE,speed);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);
}


//Print Speed
  lcd.setCursor(9, 1);
  if(speed == 255){
    lcd.print("FULL");
  }
  else if(speed == 192){
    lcd.print("3/4 ");
  }
  else if(speed == 128){
    lcd.print("1/2 ");
  }
  else{
  lcd.print("0   ");
  }

//Print Direction
  lcd.setCursor(13, 1);
  if(digitalRead(DIRA) == HIGH && (speed > 0)){
    lcd.print(" C ");
  }
  else if (digitalRead(DIRB) == HIGH && (speed > 0)){
    lcd.print(" CC");
  }
  else{
    lcd.print("N/A");
  }


  Serial.println(buttonPress);
  delay(1000);
}
