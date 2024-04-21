/**
 * @file adafruit_servo_driver.cpp
 * @author Gento Aiba
 * @brief PCA9685のサーボモータードライバとI2Cで通信するクラス
 * @version 1.0
 * @date 2024-03-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "adafruit_servo_driver.hpp"

AdaServoDriver::AdaServoDriver()
{
}

void AdaServoDriver::write8(uint8_t addr, uint8_t d)
{
    uint8_t send_data[2];

    send_data[0] = addr;
    send_data[1] = d;
    if (write(_i2c, send_data, 2) != 2)
    {
        printf("Faild to send i2c\n");
    }
}

uint8_t AdaServoDriver::read8(uint8_t addr)
{
    uint8_t send_data;
    uint8_t read_data;

    send_data = addr;
    if (write(_i2c, &send_data, 1) != 1)
    {
        printf("Failed to send i2c @read\n");
    }
    else
    {
        if (read(_i2c, &read_data, 1) != 1)
        {
            printf("Failed to read i2c\n");
        }
    }

    return read_data;
}

void AdaServoDriver::reset()
{
    write8(PCA9685_MODE1, 0x0);
}

void AdaServoDriver::setPWMFreq(float freq)
{
    float prescaleval = 25000000;

    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;
    printf("Estimated pre-scale: %f\n", prescaleval);

    uint8_t prescale = floor(prescaleval + 0.5);
    printf("Final pre-scale: %d\n", prescale);

    uint8_t oldmode = read8(PCA9685_MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10;
    write8(PCA9685_MODE1, newmode);
    write8(PCA9685_PRESCALE, prescale);
    write8(PCA9685_MODE1, oldmode);
    sleep(5);
    write8(PCA9685_MODE1, oldmode | 0xa1);
}

std::string AdaServoDriver::setPWM(uint8_t ch, uint16_t onTime, uint16_t offTime)
{
    uint8_t send_data[5];

    send_data[0] = LED0_ON_L + 4 * ch;
    send_data[1] = (uint8_t)(0x00ff & onTime);
    send_data[2] = (uint8_t)((0xff00 & onTime) >> 8);
    send_data[3] = (uint8_t)(0x00ff & offTime);
    send_data[4] = (uint8_t)((0xff00 & offTime) >> 8);

    if (write(_i2c, send_data, 5) != 5)
    {
        printf("Faild to send i2c @setPWM\n");
        return "Faild to send i2c @setPWM";
    }
    return "success to send i2c @setPWM";
}

int AdaServoDriver::setServoPulse(uint8_t ch, double pulseWidth_us)
{
    double pulse_length;
    double pulse_width;

    // 1秒=1000000usを60Hzで割ってパルス長を算出。
    pulse_length = 1000000 / freqency_;
    // 12bit(2^12=4096)分解能相当へ。1分解能当たりの時間算出。
    pulse_length /= 4096;
    // PWMのパルス設定値を算出。
    pulse_width = pulseWidth_us / pulse_length;

    // PWM値設定。
    //  setPWM(channel, on_timing, off_timing)
    //  channelで指定したチャネルのPWM出力のon(0→1）になるタイミングと
    //  off(1→0)になるタイミングを0～4095で設定する。
    setPWM(ch, 0, pulse_width);
    return pulse_width;
}

bool AdaServoDriver::openI2C(char *i2c_file_name = "/dev/i2c-1", int address = 0x40)
{
    i2c_file_name_ = i2c_file_name;
    address_ = address;

    _i2c = open(i2c_file_name_, O_RDWR);
    if (_i2c < 0)
    {
        printf("Failed to open i2c\n");
        return false;
    }
    if (ioctl(_i2c, I2C_SLAVE, address_) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave\n");
        return false;
    }
    return true;
}