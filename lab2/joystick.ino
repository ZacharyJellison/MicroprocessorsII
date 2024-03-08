//www.elegoo.com
//2016.12.09

//#include <MPU6050.h>
#include <Wire.h>

//MPU6050 mpu;

//testing getting output from joystick on the arduino
int VRx = A0;
int VRy = A1;
//int SW = 2;
int buzz = 4;

int xPosition = 0;
int yPosition = 0;
//int SW_state = 0;
int mapX = 0;
int mapY = 0;

//int incomingByte = 0;

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  //pinMode(SW, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
/*
while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
{    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
     delay(500);
}

mpu.calibrateGyro();
mpu.setThreshold(3);*/
checkSettings();
}

void checkSettings() {
Serial.println();
/*
switch(mpu.getClockSource())
{
case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
}

Serial.print(" * Gyroscope:         ");
switch(mpu.getScale())
{
case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
}
*/
}

void joystick() {
  // put your main code here, to run repeatedly:
  //see if joystick idea is correct or not
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  //SW_state = digitalRead(SW);
  //mapX = map(xPosition, 0, 1023, -10, 10);
  //mapY = map(yPosition, 0, 1023, -10, 10);
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
/*
void gyroscope(int xDir, int yDir) {
  if (xDir > 100) {
    Serial.print("D");
    delay(100);
  }

  if (xDir < -100) {
    Serial.print("A");
    delay(100);
  }

  if (yDir > 100) {
    Serial.print("W");
    delay(100);
  }

  if (yDir < -100) {
    Serial.print("S");
    delay(100);
  }
}
*/
void loop() {
if(Serial.available() > 0){
    //incomingByte = Serial.read();
    //Serial.println(incomingByte);
  /*
    if(incomingByte == 'E'){ //read incoming byte, if it is an E buzz
      // the buzzer indicating apple was eaten
      tone(buzz, 1000);
      delay(100);
      noTone(buzz);
    }
    */
  }

      //Vector rawGyro = mpu.readRawGyro();
      //Vector normGyro = mpu.readNormalizeGyro();
      
      //gyroscope(normGyro.XAxis, normGyro.YAxis);

      joystick();
}
