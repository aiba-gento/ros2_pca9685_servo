#include "servo_driver.hpp"
#include "adafruit_servo_driver.hpp"

AdaServoDriver servo;

ServoDriver::ServoDriver() : Node("servo_driver")
{
    servo.openI2C();
    servo.reset();
    servo.setPWMFreq();
}

ServoDriver::~ServoDriver()
{
}
