#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#define MPU6050_ADDR 0x68 // MPU6050 I2C address

#define ACCEL_X_CORRECTION 500
#define ACCEL_Y_CORRECTION 250
#define ACCEL_Z_CORRECTION -50



struct gyroData {
    int16_t x;
    int16_t y;
    int16_t z;
};

struct accelData {
    int16_t x;
    int16_t y;
    int16_t z;
};

class Gyro
{
public:
    // Constructor
    Gyro();
    
    accelData getAccelData();
    gyroData getGyroData();

private:
    accelData accel_data;
    gyroData gyro_data;
    void writeToMPU6050(uint8_t reg, uint8_t val);
    void readFromMPU6050(uint8_t reg, int numBytes);
};

#endif
