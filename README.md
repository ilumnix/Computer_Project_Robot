# Comp_Project_ROBOT

CSCI 1063U Robotics Project

Overview

This is a robot that is coded to go through a maze, automated. It has three infrared sensors for line tracking and an ultrasonic distance sensor to detect walls. The robot is also equipped with a gyroscope which allows precise turnings.

Structure


    elegoo_smart_car/
    ├── RobotBase1063.ino       # Main program file with setup() and loop()
    ├── sensors.h               # Sensor function declarations
    ├── sensors.cpp             # Ultrasonic, line tracking, and gyroscope implementations
    ├── motors.h                # Motor function declarations
    ├── motors.cpp              # DC motors, servo, and LED implementations
    └── README.md               



Hardware Assumptions

    - Elegoo Smart Car V4.0 - Main chassis with battery pack
    - Motor Driver - Controls DC motors, included with kit
    - DC Motor (x2) - Drive motors, included with kit
    - Ultrasonic distance sensor - connected to pins 12 and 13
    - SG90 Servo - Rotates ultrasonic sensor, connected to pin 10
    - IR line tracking sensor (x3) -  on pins A0, A1, A2
    - Gyroscope - on I2C (SDA/SCL)
    - RGB LED (x2) - connected to pin 4
    - Push Button - Start button connected to pin 2


Additional Libraries(Download if not installed)

    Install via Arduino Library Manager:

    - FastLED - WS2812B LED control
    - Servo - Servo motor control (included with Arduino IDE)
    - Wire - I2C communication (included with Arduino IDE)
	
How to Run

1. Install Arduino IDE

Download and install Arduino IDE (version 1.8.x or 2.x) from 
    [arduino.cc](https://www.arduino.cc/en/software)

2. Install Libraries

    1. Open Arduino IDE
    2. Go to `Sketch > Include Library > Manage Libraries`
    3. Search for "FastLED" and click Install

3. Upload Code

    1. Connect Arduino to computer via USB cable
    2. Open `RobotBase1063.ino` in Arduino IDE
    3. Select board: `Tools > Board > Arduino UNO`
    4. Select port: `Tools > Port > COMx` (Find the correct port)
    5. Click the Upload button (arrow icon)

4. Run the Car

    1. Disconnect USB and place car on the track
    2. Ensure battery pack is charged and is on
    3. Press the reset button on the Arduino (Just to make sure)
    4. Wait for purple LED pulse sequence (3 pulses)
    5. When LED turns white, press the start button
    6. Green LED indicates ready - car will start moving


Known Issues

    - Gyro drift - Angle accuracy degrades over time due to gyroscope drift. Reset angle frequently while doing a turn
    - Motor imbalance - Car may drift left or right when going straight. Adjusted `StraightSpeedR` and `StraightSpeedL` values to compensate.
    - Line sensor sensitivity - Different lighting conditions affect sensor readings. Recalibrated threshold values for the environment and make sure that the robot isn't going too fast.
    - **Ultrasonic false readings** - Soft or angled surfaces may not reflect sound properly. Sensor retries up to 3 times to get valid reading.
    - I2C communication - Gyro may fail to initialize if wiring is loose. Red LED at startup indicates failure; check SDA/SCL connections.
