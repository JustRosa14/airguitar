#include "gyro.h"

Gyro::Gyro() {
  Wire.begin();
  
  // Initialize MPU6050
  writeToMPU6050(0x6B, 0); // Wake up MPU6050
}

accelData Gyro::getAccelData() {
  // Read accelerometer and gyroscope data
  int16_t dummy;

  accelData t;

  readFromMPU6050(0x3B, 14); // Read 14 bytes starting from register 0x3B

  t.x = (Wire.read() << 8 | Wire.read()) + CORRECTION_X_AXIS;
  t.y = (Wire.read() << 8 | Wire.read()) + CORRECTION_Y_AXIS;
  t.z = (Wire.read() << 8 | Wire.read()) + CORRECTION_Z_AXIS;

  // Not using gyro data here
  dummy = (Wire.read() << 8 | Wire.read());
  dummy = (Wire.read() << 8 | Wire.read());
  dummy = (Wire.read() << 8 | Wire.read());

  return t;
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
