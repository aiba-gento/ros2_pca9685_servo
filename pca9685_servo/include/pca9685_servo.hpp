#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>

class PCA9685Servo : public rclcpp::Node
{
private:
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr sub_servo_angle[16];

public:
    PCA9685Servo();
    ~PCA9685Servo();

    void servo_angle_callback_1(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_2(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_3(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_4(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_5(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_6(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_7(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_8(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_9(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_10(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_11(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_12(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_13(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_14(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_15(std_msgs::msg::Float64::SharedPtr msg);
    void servo_angle_callback_16(std_msgs::msg::Float64::SharedPtr msg);
};
