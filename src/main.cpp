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
int playString(bool noise);
int determineFret();

accelData accel_data;
gyroData  gyro_data;
int lastFourValues[4] = {0, 0, 0, 0};
Gyro g;


int string; 
int fret;
int low_E_string[]  = {fE4, fF4, fGb4, fG4, fAb4};
int A_string[]      = {fA4, fBb4, fB4, fC5, fDb5};
int D_string[]      = {fD5, fEb5, fE5, fF5, fGb5};
int G_string[]      = {fG5, fAb5, fA5, fBb5, fB5};

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
  string = -1;
  fret = 0;
  g = Gyro();
  
  visualizeData(0, 1);
  visualizeData(0, 1);
}

void loop() {
  //visualizeData(0, 1);

  string = playString(analyzeStrum());
  fret = determineFret();

  switch(string){
    case 0:
      Serial.println("String 0");
      tone(D3, string1[fret], 200);
      break;
    case 1:
      Serial.println("String 1");
      tone(D3, string2[fret], 200);
      break;
    default:
      
      break;
  }




  // for(int i=0;i<9;i++){
  // Serial.print(analogRead(A0));
  // Serial.print(" "); 
  // }
  // Serial.print("\n");
  

  

  //buttonread
  //if(digitalRead(D5)){
  //}else{
  //  Serial.println("Button pressed");
  //}

}

int determineFret(){
  int temp = analogRead(A0);

  switch(temp){
    case 300 ... 400:
      return 1;
      break;
    case 401 ... 500:
      return 2;
      break;
    case 501 ... 600:
      return 3;
      break;
    case 601 ... 700:
      return 4;
      break;
    case 701 ... 800:
      return 5;
      break;
    default:
      return 0;
      break;
  }
}

int playString(bool noise){
  if(noise){
      if(!digitalRead(KNOP4)){
        return 5;
        //tone(D3, fE4, 200);
      }else if(!digitalRead(KNOP3)){
        return 4;
        //tone(D3, fA4, 200);
      }else if(!digitalRead(KNOP2)){
        return 3;
        //tone(D3, fD5, 200);
      }else if(!digitalRead(KNOP1)){
        //tone(D3, fG5, 200);
        return 2;
      }    
      else{
        //tone(D3, fB3, 200);
        return 1;
      }
    }
    else{
      return -1;
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
#ifdef SHOW_STRUM_DATA
      visualizeData(0, 1);
#endif
      if(accel_data.x < -15000){
        x_condition = true;
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



