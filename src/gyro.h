#ifndef GYRO_H
#define GYRO_H

#include <Wire.h>
#define MPU6050_ADDR 0x68 // MPU6050 I2C address

#define CORRECTION_X_AXIS 0
#define CORRECTION_Y_AXIS 0
#define CORRECTION_Z_AXIS 0

struct gyroData {
    int16_t x;
    int16_t y;
    int16_t z;
};

struct accelData {
    int x;
    int y;
    int z;
};

class Gyro
{
public:
    // Constructor
    Gyro();
    
    accelData getAccelData();
    gyroData getGyroData();

private:

    void writeToMPU6050(uint8_t reg, uint8_t val);
    void readFromMPU6050(uint8_t reg, int numBytes);
};

#endif
