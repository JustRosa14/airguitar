#include "MPU6050.h"

Gyro::Gyro() {
  Wire.begin();
  
  // Initialize MPU6050
  writeToMPU6050(0x6B, 0); // Wake up MPU6050
}

accelData Gyro::getAccelData() {
  // Read accelerometer and gyroscope data
  int16_t dummy;


  readFromMPU6050(0x3B, 14); // Read 14 bytes starting from register 0x3B
  // Not using gyro data here
  dummy = (Wire.read() << 8 | Wire.read());
  dummy = (Wire.read() << 8 | Wire.read());
  dummy = (Wire.read() << 8 | Wire.read());



  this->accel_data.x = (Wire.read() << 8 | Wire.read()) + CORRECTION_X_AXIS;
  this->accel_data.y = (Wire.read() << 8 | Wire.read()) + CORRECTION_Y_AXIS;
  this->accel_data.z = (Wire.read() << 8 | Wire.read()) + CORRECTION_Z_AXIS;



  return this->accel_data;
}

gyroData Gyro::getGyroData(){
  int16_t dummy;

  readFromMPU6050(0x3B, 14);

  // Not using accel data here
  dummy = (Wire.read() << 8 | Wire.read());
  dummy = (Wire.read() << 8 | Wire.read());
  dummy = (Wire.read() << 8 | Wire.read());

  this->gyro_data.x = (Wire.read() << 8 | Wire.read()) + 5900;
  this->gyro_data.y = (Wire.read() << 8 | Wire.read()) + 400;
  this->gyro_data.z = (Wire.read() << 8 | Wire.read()) + 300;

  return this->gyro_data;
}

void Gyro::writeToMPU6050(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void Gyro::readFromMPU6050(uint8_t reg, int numBytes) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(MPU6050_ADDR, numBytes);
}
