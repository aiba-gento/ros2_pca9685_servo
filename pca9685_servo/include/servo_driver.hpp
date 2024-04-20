#include <rclcpp/rclcpp.hpp>

class ServoDriver : public rclcpp::Node
{
private:
    char *i2c_file_name_;
    int address_;

public:
    ServoDriver(/* args */);
    ~ServoDriver();
};