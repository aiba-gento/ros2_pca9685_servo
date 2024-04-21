# PCA9685 Servo Driver Node
PCA9685というチップとI2C通信してサーボモーターを動かすノードです。
## parameter
x: サーボモーターのチャンネル
|parameter名|型|説明|
|:-:|:-:|:-:|
|freqency|double|PWMの周波数|
|servo_num|int|使用するサーボモーターの数|
|servo_x.pulse_range|double|PWMのパルス幅の範囲[us]|
|servo_x.pulse_center|double|PWMのパルス幅の中央値[us]|
|i2c_file_name|string|I2Cデバイスのパス("/dev/i2c-1")|
|driver_address|int|PCA9685のアドレス|

# subscriber
x: サーボモーターのチャンネル
|topic名|型|内容|
|:-:|:-:|:-:|
|/servo/_x/angle|std_msgs::msg::Float64|サーボモーターの角度|