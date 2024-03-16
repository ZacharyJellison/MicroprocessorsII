#include <Wire.h>
#include <MPU6050.h> 

//testing getting output from joystick on the arduino
int VRx_pin = A0;
int VRy_pin = A1;

int buzz = 4;
int incomingByte = 0;

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  pinMode(VRx_pin, INPUT);
  pinMode(VRy_pin, INPUT);
  pinMode(buzz, OUTPUT);
  checkSettings();

  Wire.begin();
  mpu.initialize();
}

void checkSettings() {
  Serial.println();
}

void joystick() {

  int xPosition = analogRead(VRx_pin);
  int yPosition = analogRead(VRy_pin);

  if(yPosition >= 800 && yPosition <= 1023){
    Serial.print("w");
    delay(100);
  } else if(xPosition >= 0 && xPosition <= 300){
    Serial.print("a");
    delay(100);
  } else if(yPosition >= 0 && yPosition <= 300){
    Serial.print("s");
    delay(100);
  } else if(xPosition >= 800 && xPosition <= 1023){
    Serial.print("d");
    delay(100);
  }
}


void gyroscope() {

  int16_t ax, ay, az, gx, gy, gz;

  // Read accelerometer and gyroscope data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
/*
  Print gyroscope data
  Serial.print("Gyroscope: ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.println(gz);
*/
  delay(100);

  if(gy > 10000){
    Serial.print("w");
    delay(100);
  } else if(gx <= -10000){
    Serial.print("a");
    delay(100);
  } else if(gy <= -10000){
    Serial.print("s");
    delay(100);
  } else if(gx >= 10000){
    Serial.print("d");
    delay(100);
  }
}

void buzzer() {
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    Serial.println(incomingByte); // Read byte coming from snake program

    if(incomingByte == 'E'){
      // Apple was eaten, ring the buzzer
      tone(buzz, 1000);
      delay(100);
      noTone(buzz);
    }
  }
}

void loop() {
  buzzer();
  joystick();
  gyroscope();
}
