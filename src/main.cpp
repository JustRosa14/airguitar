#include <Arduino.h>

#include "MPU6050.h"
#define PRINT_TRIGGER

accelData accel_data;
gyroData  gyro_data;
int lastFourValues[4] = {0, 0, 0, 0};
Gyro g;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Hello, World! Waiting a few seconds");
  delay(2000);
  analogWrite(D3, 0);
  
  g = Gyro();
}

void loop() {
  
  accel_data = g.getAccelData();
  gyro_data = g.getGyroData();

  Serial.print("AccelX: "); Serial.print(accel_data.x);
  Serial.print("\tAccelY: "); Serial.print(accel_data.y);
  Serial.print("\tAccelZ: "); Serial.print(accel_data.z);

 //currently the "gyro" data seems to represent the accel data, check this
   Serial.print("\tGyroX: "); Serial.print(gyro_data.x);
   Serial.print("\tGyroY: "); Serial.print(gyro_data.y);
   Serial.print("\tGyroZ: "); Serial.println(gyro_data.z);

  //buttonread
  //if(digitalRead(D5)){
  //}else{
  //  Serial.println("Button pressed");
  //}

}

void analyzeStrum(){
  int makeNoise = 0;
  int x_condition = 0;
  int y_condition = 0;
  int z_condition = 0;
  accelData data = g.getAccelData();

  if(data.y < 10000){
    Serial.println("Triggered!"); 
    for(int i=0;i<10;i++){
      data = g.getAccelData();
#ifdef PRINT_TRIGGER
      Serial.print("AccelX: "); Serial.print(data.x);
      Serial.print("\tAccelY: "); Serial.print(data.y);
      Serial.print("\tAccelZ: "); Serial.println(data.z);
#endif
      if(data.z < 10000){
        z_condition = 1;
      }

      if(data.y > 10000){
        y_condition = 1;
      }

      if(z_condition && (data.z > 10000  || y_condition)){
        
        makeNoise = 1;
      }

    }
    x_condition = 0;
    y_condition = 0;
    z_condition = 0; 
  }

  if(makeNoise){
    Serial.println("Making noise");
    analogWrite(D3, 250);
    delay(1000);
    analogWrite(D3, 0);
  }
  //delay(200);  // Adjust the delay based on your requirements
}




