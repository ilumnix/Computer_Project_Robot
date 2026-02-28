/*
 * sensors.h - Sensor Interface Header
 * CSCI 1063U - Elegoo Smart Car V4.0
 * 
 * This header defines the interface for all sensor operations including:
 * - Ultrasonic distance sensor
 * - Line tracking sensors (left, middle, right)
 * - Gyroscope (MPU6050)
 */

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>

// ====== PIN DEFINITIONS ======
#define US_OUT 13             // Ultrasonic Sensor Trigger Pin
#define US_IN 12              // Ultrasonic Sensor Echo Pin
#define LEFT A2               // Left Line Tracker
#define MIDDLE A1             // Center Line Tracker
#define RIGHT A0              // Right Line Tracker
#define GYRO 0x68             // MPU6050 I2C Address

// ====== LINE SENSOR THRESHOLDS ======
#define LEFTCVALUE 400
#define MIDDLECVALUE 300
#define RIGHTCVALUE 400

// ====== SHARED VARIABLES ======
extern unsigned long lastTime;  // Last read time for gyro calculations

// ====== FUNCTION DECLARATIONS ======

/**
 * Initialize all sensor pins
 * Call this once in setup()
 */
void initSensors();

/**
 * Get distance to nearest obstacle using ultrasonic sensor
 * @return Distance in centimeters (0-200), or 0 if invalid
 */
int getDistance();

/**
 * Initialize the MPU6050 gyroscope
 * @return true if initialization successful, false if communication failed
 */
bool setupGyro();

/**
 * Calibrate the gyroscope by measuring drift at rest
 * IMPORTANT: The car must be completely stationary during calibration!
 */
void calibrateGyro();

/**
 * Update the current angle based on gyroscope readings
 * MUST be called frequently for accurate angle tracking
 */
void updateGyroAngle();

/**
 * Reset the tracked angle to zero
 */
void resetAngle();

/**
 * Get the current tracked angle
 * @return Angle in degrees (-180 to +180)
 */
float getAngle();

/**
 * Read raw Z-axis gyroscope value
 * @return Raw 16-bit signed value from gyroscope
 */
int16_t readGyroZ();

#endif // SENSORS_H 