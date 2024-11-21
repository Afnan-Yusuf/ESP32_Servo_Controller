#include <Arduino.h>
#include <ESP32Servo.h>
#include "eyeblink.h"

Servo servoLeft;
Servo servoRight;

#define servoLeftpin 13
#define servoRightpin 12
int leftAngle = 90;          // Initial angle for left servo
int rightAngle = 90;         // Initial angle for right servo

const int leftMin = 60;      // Minimum angle for left servo
const int leftMax = 120;     // Maximum angle for left servo
const int rightMin = 60;     // Minimum angle for right servo
const int rightMax = 120;    // Maximum angle for right servo

int leftDirection = 1;       // Direction for left servo movement
int rightDirection = -1;     // Direction for right servo movement

unsigned long previousMillis1 = 0;  // Stores the last time servos were updated
const int servoSpeed = 20;         // Time interval between updates (ms)
void setup() {
  initeyedisplay();
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servoLeft.setPeriodHertz(50);    // standard 50 hz servo
	servoLeft.attach(servoLeftpin, 1000, 2000);
  servoRight.setPeriodHertz(50);    // standard 50 hz servo
  servoRight.attach(servoRightpin, 1000, 2000);

  servoLeft.write(leftAngle);  // Set initial position
  servoRight.write(rightAngle);

}

void loop() {
  eyeblink();
  unsigned long currentMillis = millis();

  // Check if it's time to update servo positions
  if (currentMillis - previousMillis1 >= servoSpeed) {
    previousMillis1 = currentMillis;

    // Update left servo position
    leftAngle += leftDirection;
    if (leftAngle <= leftMin || leftAngle >= leftMax) {
      leftDirection *= -1; // Reverse direction at boundaries
    }
    servoLeft.write(leftAngle);

    // Update right servo position
    rightAngle += rightDirection;
    if (rightAngle <= rightMin || rightAngle >= rightMax) {
      rightDirection *= -1; // Reverse direction at boundaries
    }
    servoRight.write(rightAngle);
  }
}
