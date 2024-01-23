#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#define MPU6050_ADDR 0x68 // MPU6050 I2C address

#define CORRECTION_X_AXIS 5900
#define CORRECTION_Y_AXIS 400
#define CORRECTION_Z_AXIS 300

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
    accelData accel_data;
    gyroData gyro_data;
    void writeToMPU6050(uint8_t reg, uint8_t val);
    void readFromMPU6050(uint8_t reg, int numBytes);
};

#endif
