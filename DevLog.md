## Development Log

### 2019-06-02
Built up a Tamiya tracked chassis as a test bed.  I think the motors on the metal tank chassis required more power than the arduino can provide.

Attempted to run the arduino and motors off of a 6V AA battery bank but the motors seem to draw too much power.  Upgrading to 9V to see if this fixes things.

Still getting weird behavior when running with 9V.  There is 7-8V at the output from the motor shield which should be plenty for the motors.

#### 2019-03-18
Wondering if I should use multiple Arduinos.  Say, one for sensing, another for position data and driving.  This might help with data rx/tx pin limitations.

#### 2019-03-16
Read through the Sparkfun [9DoF Razor IMU M0 tutorial](https://learn.sparkfun.com/tutorials/9dof-razor-imu-m0-hookup-guide?_ga=2.127353869.1406852289.1552693386-171387036.1551586549).

* Installed required libraries:

  Arduino SAMD Boards (32-bits ARM Cortex-M0+)
  [Sparkfun SAMD Boards](https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json)
  SparkFun MPU-9250 Digital Motion Processing (DMP) library
  FlashStorage Arduino library


#### 2019-03-15
Read through the Sparkfun:

* [GPS Basics tutorial](https://learn.sparkfun.com/tutorials/gps-basics)
* [Serial communication tutorial](https://learn.sparkfun.com/tutorials/serial-communication)
* [I2C tutorial](https://learn.sparkfun.com/tutorials/i2c)

I bought the wrong stackable header for the GPS logger shield.  I purchased the same header kit used for the Ardumotor shield ([PRT-10007](https://www.sparkfun.com/products/10007)) which has 2 x 8 pin and 2 x 6 pin connectors.  The GPS logger shield requires [PRT-11417](https://www.sparkfun.com/products/11417) which includes 2 x 8 pin, 1 x 6 pin, and 1 x 10 pin connectors.  I guess I'll move on to another module until the correct headers arrive.

#### 2019-03-13
* Finished chassis wiring and uploaded motor shield test file. Running off of USB power is insufficient.  A 9V battery seems barely sufficient.  The motors on the chassis specify 12V. Unfortunately the Sparkfun website is down at the moment so I am unable to verify the maximum voltage the motor shield can safely handle.
* Follow up: When powering the motor shield through its own Voltage in terminal power is sent from the motor shield to the Arduino, meaning that the voltage the Arduino can accept is the limiting factor. According to the [Arduino store](https://store.arduino.cc/usa/arduino-uno-rev3) the Uno can take 6-20V.  The Sparkfun [hookup guide](https://learn.sparkfun.com/tutorials/ardumoto-kit-hookup-guide?_ga=2.243238086.5142335.1552538843-171387036.1551586549) suggests that the acceptable range of an Arduino is usually 6-15V.
* Next step: Setup GPS Logger shield.

#### 2019-03-09
* Created repo.
* Added parts list and photos.
* Ran through the [motor shield hookup guide](https://learn.sparkfun.com/tutorials/ardumoto-kit-hookup-guide?_ga=2.13287927.1329533407.1552159196-171387036.1551586549)