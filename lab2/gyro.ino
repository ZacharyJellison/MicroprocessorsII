#include <Wire.h>
#include <MPU6050.h> 

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  mpu.initialize();
}


void gyroscope() {

  int16_t ax, ay, az, gx, gy, gz;

  // Read accelerometer and gyroscope data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
/*
  Print gyroscope data
  Serial.print("Gyroscope (°/s): ");
  Serial.print(gx); Serial.print(", ");
  Serial.print(gy); Serial.print(", ");
  Serial.println(gz);
*/
  delay(100); // Delay for stability

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

void loop() {
  gyroscope();
  joystick();
}