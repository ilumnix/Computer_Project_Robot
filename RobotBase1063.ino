/*
 * elegoo_smart_car.ino - Main Program
 * CSCI 1063U - Elegoo Smart Car V4.0
 *
 * Starter Code for motor, pin, && sensor setup
 * Provided to students for use && understanding
 */

#include <Wire.h>
#include <FastLED.h>
#include <Servo.h>
#include "sensors.h"
#include "motors.h"

// ====== PIN DEFINITIONS ======
#define BUTTON 2              // Push Button

// ====== PROGRAM VARIABLES ======
unsigned long stuckStartTime = 0;  // When car stopped moving
bool isStuck = false;

// Need to expose lastTime for turn functions
extern unsigned long lastTime;

void setup() {
  // Initialize hardware modules
  initMotors();
  initSensors();
  
  // Button pin
  pinMode(BUTTON, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);
  
  // Startup LED pattern - purple pulse
  for (int i = 0; i < 3; i++) {
    ledOn(CRGB::Purple);
    delay(200);
    ledOff();
    delay(200);
  }
  
  // Button Pressed - Led turn white for a bit
  ledOn(CRGB::White);
  while (digitalRead(BUTTON) == HIGH) {
    
  }

  delay(100);
  // LED turns Red - Gyro's not working
  if (!setupGyro()) {
    ledOn(CRGB::Red);
    while (true);  
  }

  calibrateGyro();
  
  //LED turns green - Good to go
  ledOn(CRGB::Green);
  delay(1000);
}


void loop() {
  // make sure motors are on and servo is centered at the start of each loop
  digitalWrite(MTR_ENABLE, HIGH);
  centerServo();
  
  // reset the angle tracker so we start fresh each time through the loop
  resetAngle();
  
  // check how far away the nearest obstacle is using ultrasonic sensor
  int distance = getDistance();
  
  // read all three line sensors to see what's under the car
  // lower values mean the sensor sees the black line
  int leftValue = analogRead(LEFT);
  int middleValue = analogRead(MIDDLE);
  int rightValue = analogRead(RIGHT);
  
  
  // first priority, if something is really close (less than 5cm), just stop
  //prevents crashes into obstacles or walls
  if (distance < 5 && distance != 0) {
    stopMotors();
    ledOn(CRGB::Orange);  // orange means we're stopped due to obstacle
  }
  
  // if there's nothing close, can move
  else if (distance > 5 || distance == 0) {
    isStuck = false;  // we're not stuck if we're moving
    
    
    // check if all three sensors see the line (or all see white)
    
    if ((leftValue < LEFTCVALUE && middleValue < MIDDLECVALUE && rightValue < RIGHTCVALUE) || (leftValue>950 && middleValue>950 && rightValue>950)) {
      resetAngle();      // reset gyro before turning
      goBack();          // back up a bit first
      delay(300);
      turn90R();         // turn right 90 degrees using gyro
      delay(250);
      ledOn(CRGB::Green);  // green means  moving
    }
    
    // if just the left sensor sees the line, turnright
    
    else if (leftValue < LEFTCVALUE) {
      turnRight();
      ledOn(CRGB::Green);  
    }
    
    // if just the right sensor sees the line, turn left
    
    else if (rightValue < RIGHTCVALUE) {
      turnLeft();
      ledOn(CRGB::Green);  
    }
    
    // if none of the sensors see the line, in the clear
    
    else if (leftValue > LEFTCVALUE && middleValue > MIDDLECVALUE && rightValue > RIGHTCVALUE) {
      goStraight();
      delay(250);        
      ledOn(CRGB::Red);  // red means exploring 
      delay(LOOP_DELAY);
    }
  }
}
