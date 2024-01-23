#include <Arduino.h>

#include "gyro.h"
#define PRINT_TRIGGER

accelData data;
int lastFourValues[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Hello, World! Waiting a few seconds");
  delay()
  analogWrite(D3, 0);
  
}

void loop() {
  Gyro g = Gyro();
  data = g.getAccelData();
  int makeNoise = 0;
  int x_condition = 0;
  int y_condition = 0;
  int z_condition = 0;

  //buttonread
  //if(digitalRead(D5)){
  //}else{
  //  Serial.println("Button pressed");
  //}

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
  }else{
    Serial.println("Not making noise");
  }

  //delay(200);  // Adjust the delay based on your requirements
}




