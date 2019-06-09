## Development Log

### 2019-06-02 - 2019-06-07
Built up a Tamiya tracked chassis as a test bed.  I think the motors on the metal tank chassis required more power than the arduino can provide.

Attempted to run the arduino and motors off of a 6V AA battery bank but the motors seem to draw too much power.  Upgrading to 9V to see if this fixes things.

Still getting weird behavior when running with 9V.  There is 7-8V at the output from the motor shield which should be plenty for the motors.

Turns out that a 9V battery is not sufficient to supply the Arduino board and the motor.
Wiring up a set of AA batteries to provide 12V through the Ardumoto dev-14129 shield succesfully drives the motor.

I'm having difficulty measuring motor draw for both the 130 type motors on the Tamiya gearbox and the motors on the metal chassis.

If I understand correctly, amerage must be measured in series.  A simple circuit where the ammeter is connected between the battery and the motor *should* work but when I insert the ammeter into the circuit nothing runs.  The motor runs fine when the wires that would connect the ammeter are connected directly.

Solutions:
Run the 6V battery banks in parallel to increase the amperage available while providing voltage sufficient for the Arduino (7V-12V) and closer to the motor specs (3V).  Purchased a 130 Type motor that operates at 6V/800mAmp stall from Pololu.com

Need to check which program is loaded onto the Arduino.  Either there is not enough current to run both motors or not all command from TestMotorShield.ino are enabled at this time.

I think a motor driver where the power to the arduino for logic and power to the motors is completely separate would be much preferable.

The test program is supposed to:
1. Run motor A backward
2. Run motor A forward
3. Run motor B backward
4. Run motor B forward
5. Run motors A & B forward
6. Run motors A & B backward
7. Run motor A forward while motor B runs backward

Using 3 banks of 4 AA batteries the test program runs steps 1-6 fine but step 7 is not running as expected.
Maybe stop the motors before having them run in opposition?

There is definitely an issue with running the motors in opposition. The addition of delays/stopping the motors before running in opposition does not do anything.

Going to try switching out the motors that came with the kit for Polulu [#1117](https://www.pololu.com/product/1117).

Agh!  The issue was definitely the cheap motors that came with the Tamiya kit.  Swapping for the Pololu 1117's runs perfectly.  They run on a 9V battery for bank of 4xAA (6V) just fine.  Lesson learned- Don't use cheap motor.  Next time I should probably just go with/learn about continuos rotation servos.

So-
2 banks of 4xAA batteries runs the test program ok.
1/2 speed is pretty weak.

Lots of wasted time on the Tamiya motors.  Upside is that I built some tooling and learned a few thing/learned that I need to learn a few things.

- Put together a bunch of jumper wires with bladed connectors
- Made 2 4xAA battery holders with bladed connectors
- Made a 4xAA battery holder with bladed connectors and barrel connector
- Decided that I need to get a better multimeter
- Learned what an 'H bridge' is. re: L298N motor drivers
- Need to learn more about the L298N and motor drivers in general
- I think there is value in completely separating the electrical input for the motors from the electrical input to the Arduino for logic.  The motor driver board I have may be capable of this but by default voltage is sent down to the Arduino from the motor driver.  I'm not sure, but it way be regulated down to 5V or so before being sent to the Arduino.

Ref:
https://www.robotshop.com/community/forum/t/using-arduino-and-l298n-to-control-tamiya-twin-motor-gearbox/6825

https://arduino.stackexchange.com/questions/1314/how-can-i-connect-the-tamiya-double-gearbox-to-arduino-uno

https://forum.arduino.cc/index.php?topic=132225.0

https://www.pololu.com/docs/0J11?utm_source=rb-community&utm_medium=forum&utm_campaign=using-arduino-and-l298n-to-control-tamiya-twin-motor-gearbox

https://www.pololu.com/product/120

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