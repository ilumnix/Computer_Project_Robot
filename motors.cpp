/*
 * motors.cpp - Motor Control Implementation
 * CSCI 1063U - Elegoo Smart Car V4.0
 * 
 * Implementation of DC motor, servo, and LED control functions.
 */

#include "motors.h"
#include "sensors.h"  // Needed for gyro functions in precision turns

// ====== PRIVATE VARIABLES ======
CRGB leds[NUM_LEDS];          // Current LED Color values
Servo scanServo;              // Servo

// ====== INITIALIZATION ======

void initMotors() {
  // setup LED
  FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS);
  FastLED.setBrightness(50); // 0-255
  
  // Motor pins
  pinMode(PWR_R, OUTPUT);
  pinMode(PWR_L, OUTPUT);
  pinMode(MTR_L, OUTPUT);
  pinMode(MTR_R, OUTPUT);
  pinMode(MTR_ENABLE, OUTPUT);
  
  // Enable motor driver
  digitalWrite(MTR_ENABLE, HIGH);

  // Initialize Servo motor
  scanServo.attach(SERVO);
  centerServo();
}

// ====== MOTOR FUNCTIONS ======

void stopMotors() {
  analogWrite(PWR_R, 0);
  analogWrite(PWR_L, 0);
}

void goStraight() {
  analogWrite(PWR_R, StraightSpeedR);
  analogWrite(PWR_L, StraightSpeedL);
  digitalWrite(MTR_R, HIGH);
  digitalWrite(MTR_L, HIGH);
}

void goBack() {
  analogWrite(PWR_R, MOTOR_SPEED);
  analogWrite(PWR_L, MOTOR_SPEED);
  digitalWrite(MTR_R, LOW);
  digitalWrite(MTR_L, LOW);
}

void turnRight() {
  analogWrite(PWR_R, TURN_SPEED);
  analogWrite(PWR_L, TURN_SPEED);
  digitalWrite(MTR_R, LOW);   
  digitalWrite(MTR_L, HIGH);  
}

void turnLeft() {
  analogWrite(PWR_R, TURN_SPEED);
  analogWrite(PWR_L, TURN_SPEED);
  digitalWrite(MTR_R, HIGH);  
  digitalWrite(MTR_L, LOW);   
}

void turn180() {
  // this function uses the gyroscope to do a precise 180 degree turn
  
  // reset the angle to zero so we know where we're starting from
  resetAngle();
  lastTime = millis();  // record current time for gyro calculations
  
  analogWrite(PWR_R, TURN_180_SPEED);
  analogWrite(PWR_L, TURN_180_SPEED);
  digitalWrite(MTR_R, HIGH);  // right motor forward
  digitalWrite(MTR_L, LOW);   // left motor backward
  
  // keep turning until we've rotated 175 degrees 
  // the gyro tells exactly how far we've turned
  while (abs(getAngle()) < TURN_180_ANGLE) {
    updateGyroAngle();  // constantly update the angle reading from gyro
    delay(10);
  }
  
  // turned far enough, stop the motors
  stopMotors();
  delay(500);  // pause for half a second to let everything settle
}

void turn90R() {
  // does a 90 degree right turn using gyro feedback
  // "R" stands for right turn
  
  // zero out the gyro angle before start turning
  resetAngle();
  lastTime = millis();  // grab the current time for gyro math
  
  analogWrite(PWR_R, TURN_180_SPEED);
  analogWrite(PWR_L, TURN_180_SPEED);
  digitalWrite(MTR_R, HIGH);  // right motor goes forward
  digitalWrite(MTR_L, LOW);   // left motor goes backward 
  
  // update the angle once before entering the loop
  updateGyroAngle();
 
  // keep spinning until turned 89 degrees (basically 90)
  // abs() because angle might be negative depending on turn direction
  while (abs(getAngle()) < 89) {
    updateGyroAngle();  // keep reading gyro to track how far we've turned
  }
  
  // done turning, update angle one last time and stop
  updateGyroAngle();
  stopMotors();
  delay(500);  
}

// ====== LED FUNCTIONS ======

void ledOn(CRGB color) {
  leds[0] = color;
  leds[1] = color;  
  FastLED.show();
}

void ledOff() {
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  FastLED.show();
}

// ===== SERVO FUNCTIONS =====

void setServoAngle(int angle) {
  static int lastAngle = -1;
  angle = constrain(angle, 0, 180);

  if (angle != lastAngle) {
    scanServo.write(angle);
    delay(15);  // Allow servo to settle
    lastAngle = angle;
  }
}

void centerServo() {
  setServoAngle(90);
}