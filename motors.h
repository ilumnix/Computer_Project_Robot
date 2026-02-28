/*
 * motors.h - Motor Control Interface Header
 * CSCI 1063U - Elegoo Smart Car V4.0
 * 
 * This header defines the interface for motor and actuator operations:
 * - DC drive motors (left and right)
 * - Servo motor for ultrasonic sensor scanning
 * - RGB LEDs for status indication
 */

#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Servo.h>
#include <FastLED.h>

// ====== PIN DEFINITIONS ======
#define NUM_LEDS 2            // Number of RGB LEDs on the car
#define PIN_RBGLED 4          // NeoPixel LED data pin
#define PWR_R 5               // Right Motor PWM (speed control)
#define PWR_L 6               // Left Motor PWM (speed control)
#define MTR_R 8               // Right Motor Direction
#define MTR_L 7               // Left Motor Direction
#define SERVO 10              // Servo Motor signal pin
#define MTR_ENABLE 3          // Motor Driver Enable pin

// ====== SPEED SETTINGS ======
#define StraightSpeedR 31
#define StraightSpeedL 31.5

#define SPEED_NORMAL 150
#define SPEED_TURN 100
#define LINE_THRESHOLD 900

#define MOTOR_SPEED 50
#define TURN_SPEED 50

// ====== DELAY SETTINGS ======
#define LOOP_DELAY 75
#define TURN_DELAY 20

// ====== TURN 180 SETTINGS ======
#define TURN_180_SPEED 100
#define TURN_180_THRESHOLD 700
#define TURN_180_ANGLE 175

// ====== FUNCTION DECLARATIONS ======

/**
 * Initialize all motor pins, servo, and LEDs
 * Call this once in setup()
 */
void initMotors();

/**
 * Stop both motors immediately
 */
void stopMotors();

/**
 * Drive the car forward in a straight line
 */
void goStraight();

/**
 * Drive the car backward
 */
void goBack();

/**
 * Turn the car to the right
 */
void turnRight();

/**
 * Turn the car to the left
 */
void turnLeft();

/**
 * Execute a precise 180-degree turn using gyroscope feedback
 */
void turn180();

/**
 * Execute a precise 90-degree right turn using gyroscope feedback
 */
void turn90R();

/**
 * Turn on both LEDs with the specified color
 * @param color CRGB color value
 */
void ledOn(CRGB color);

/**
 * Turn off both LEDs
 */
void ledOff();

/**
 * Set the servo to a specific angle
 * @param angle Target angle in degrees (0-180)
 */
void setServoAngle(int angle);

/**
 * Center the servo (90 degrees)
 */
void centerServo();

#endif // MOTORS_H