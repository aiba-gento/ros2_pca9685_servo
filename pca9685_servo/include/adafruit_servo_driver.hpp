/**
 * @file adafruit_servo_driver.hpp
 * @author Gento Aiba
 * @brief PCA9685のサーボモータドライバとI2Cで通信するクラス
 * @version 1.0
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
// Ada I2C 16chサーボドライバ
#include <cmath> // for floor function
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>
// #include <linux/i2c-dev.h>
// #include <linux/i2c.h>

// Ada 16ch PWMサーボドライバクラス

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

class AdaServoDriver
{
private:
    double freqency_ = 60;
    char *i2c_file_name_ = "/dev/i2c-1"; // I2Cデバイスのパス（古いものはi2c-0）
    int address_ = 0x41;                 // ドライバのI2Cアドレス

public:
    AdaServoDriver();
    void reset();
    void setPWMFreq(float freq);
    int setServoPulse(uint8_t ch, double pulseWidth_us);
    bool openI2C(char *i2c_file_name, int address);

private:
    uint8_t read8(uint8_t addr);
    void write8(uint8_t addr, uint8_t d);
    std::string setPWM(uint8_t srvNo, uint16_t onTime, uint16_t offTime);
    uint8_t _i2cAddr;
    int _i2c;
};