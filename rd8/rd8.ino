#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define BACK_LEFT 2
#define BACK_RIGHT 3
#define FEMUR 50

#include "LegServo.h"

// Servos
Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver(0x40);

LegServo servos[8] = { // 270 degrees pwm 100 to 505
  LegServo(&driver, 6, 228,  90), // Front Left Hip - 0 degrees is forward - 235
  LegServo(&driver, 7, 126,  21.9865), // Front Left Knee - 0 degrees is vertical - 145
  LegServo(&driver, 4, 363, 180), // Front Right Hip - 270 degrees is forward - 370
  LegServo(&driver, 5, 470, 248.0135), // Front Right Knee - 270 degrees is vertical - 460
  LegServo(&driver, 0, 238,  90), // Back Left Hip
  LegServo(&driver, 1, 136,  21.9865), // Back Left Knee
  LegServo(&driver, 2, 370, 180), // Back Right Hip
  LegServo(&driver, 3, 460, 248.0135), // Back Right Knee
};

Leg legs[4] = {
  Leg(&servos[0], &servos[1], false, 2), // Front Left
  Leg(&servos[2], &servos[3], true,  2), // Front Right
  Leg(&servos[4], &servos[5], false, 2), // Back Left
  Leg(&servos[6], &servos[7], true,  2), // Back Right
};

#define CLOCK_CYCLE 20
unsigned long currentMs;
unsigned long prevMs;

void setup() {
  Serial.begin(115200);
  //while (!Serial) yield();
  Serial.println("Robot Dog - 8 Servo");

  // start servos
  driver.begin();
  driver.setOscillatorFrequency(25000000);
  driver.setPWMFreq(50);

  delay(100);
  //centerServos();
  stand();
  delay(1000);

  prevMs = millis();
}

void loop() {
  currentMs = millis();
  if((currentMs - prevMs) < CLOCK_CYCLE) return;
  prevMs = currentMs;

  //centerServos();
  //stand();
  //lay();
  //balanceTest();
  //trotInPlace();
  staticWalk4();

  //delay(1000);
}
