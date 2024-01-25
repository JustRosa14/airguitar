#include "MPU6050.h"

Gyro::Gyro() {
  Wire.begin();
  this->accel_data.x = -2;
  this->accel_data.y = -2;
  this->accel_data.z = -2;

  this->gyro_data.x = -2;
  this->gyro_data.y = -2;
  this->gyro_data.z = -2;
  // Initialize MPU6050
  writeToMPU6050(0x6B, 0); // Wake up MPU6050
}

accelData Gyro::getAccelData() {
  // Read gyroscope data
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x43); // Start reading from register 0x43 (gyro data starts from here)
  Wire.endTransmission();

  Wire.requestFrom(MPU6050_ADDR, 6); // Request 6 bytes (2 bytes per axis)

  // Not using accel data here
  this->accel_data.x = (Wire.read() << 8 | Wire.read()) + ACCEL_X_CORRECTION;
  this->accel_data.y = (Wire.read() << 8 | Wire.read()) + ACCEL_Y_CORRECTION;
  this->accel_data.z = (Wire.read() << 8 | Wire.read()) + ACCEL_Z_CORRECTION;

  if((accel_data.x == ACCEL_X_CORRECTION) && accel_data.y == ACCEL_Y_CORRECTION){
   
  }

  return this->accel_data;
}

gyroData Gyro::getGyroData() {
  // Read gyroscope data
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B); // Start reading from register 0x43 (gyro data starts from here)
  Wire.endTransmission();

  Wire.requestFrom(MPU6050_ADDR, 6); // Request 6 bytes (2 bytes per axis)

  this->gyro_data.x = (Wire.read() << 8 | Wire.read()) + 4400;
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
