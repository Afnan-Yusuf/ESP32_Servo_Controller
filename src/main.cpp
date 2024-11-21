#include <Arduino.h>
#include <ESP32Servo.h>
#include "eyeblink.h"

Servo servo1;
Servo servo2;

#define servo1pin 13
#define servo2pin 12

void setup() {
  initeyedisplay();
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo1.setPeriodHertz(50);    // standard 50 hz servo
	servo1.attach(servo1pin, 1000, 2000);
  servo2.setPeriodHertz(50);    // standard 50 hz servo
  servo2.attach(servo2pin, 1000, 2000);

}

void loop() {
  eyeblink();
  //sweep bot servos
  for (int i = 0; i <= 180; i++) {
    servo1.write(i);
    servo2.write(i);
    delay(15);
  }
  for (int i = 180; i >= 0; i--) {
    servo1.write(i);
    servo2.write(i);
    delay(15);
  }
}
