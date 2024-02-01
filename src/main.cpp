#include <Arduino.h>
#include <stdbool.h>
#include "MPU6050.h"
#include "frequencies.h"

#define KNOP4 D4
#define KNOP3 D7
#define KNOP2 D6
#define KNOP1 D5

void visualizeData(bool gyro, bool accel);
bool analyzeStrum();
void makeNoise(bool noise);

accelData accel_data;
gyroData  gyro_data;
int lastFourValues[4] = {0, 0, 0, 0};
Gyro g;

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Serial.print("Hello, World! Waiting a few seconds..");

  Serial.print("v\n");

  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D3, OUTPUT);
  
  g = Gyro();

}

void loop() {
  //visualizeData(0, 1);

  makeNoise(analyzeStrum());



  

  

  

  //buttonread
  //if(digitalRead(D5)){
  //}else{
  //  Serial.println("Button pressed");
  //}

}

void makeNoise(bool noise){
  if(noise){
      Serial.println("Making noise");
      if(!digitalRead(KNOP4)){
        tone(D3, fE4, 200);
      }else if(!digitalRead(KNOP3)){
        tone(D3, fA4, 200);
      }else if(!digitalRead(KNOP2)){
        tone(D3, fD5, 200);
      }else if(!digitalRead(KNOP1)){
        tone(D3, fG5, 200);
      }    
      else{
        tone(D3, fB3, 200);
      }
    }
}

bool analyzeStrum(){
  bool x_condition = false;
  bool y_condition= false;
  bool z_condition = false;

  accel_data = g.getAccelData();
  if(accel_data.y < -10000){
    for(int i=0;i<10;i++){
      accel_data = g.getAccelData();
      visualizeData(0, 1);
      if(accel_data.x < -15000){
        x_condition = true;
        Serial.println("x_condition Done");
      }
      if(x_condition){
        return true;
      }
    }

    

  }
  return false;
}

void visualizeData(bool gyro, bool accel){
  Gyro t = Gyro();
  if(accel){
      accel_data = g.getAccelData();
      Serial.print("AccelX: "); Serial.print(accel_data.x);
      Serial.print("\tAccelY: "); Serial.print(accel_data.y);
      Serial.print("\tAccelZ: "); Serial.print(accel_data.z);
      if(!gyro){
        Serial.print("\n");
      }
  }
  if(gyro){
      gyro_data = g.getGyroData();
      if(accel){
        Serial.print("\t");
      }
      Serial.print("GyroX: "); Serial.print(gyro_data.x);
      Serial.print("\tGyroY: "); Serial.print(gyro_data.y);
      Serial.print("\tGyroZ: "); Serial.println(gyro_data.z);
  }



}



