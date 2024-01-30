#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "LegServo.h"



// Servos
Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver(0x40);
#define SERVO_FREQ 50

LegServo servos[8] = { // 270 degrees pwm 100 to 505
  LegServo(&driver, 6, 228,  90), // Front Left Hip - 0 degrees is forward - 235
  LegServo(&driver, 7, 126,  30), // Front Left Knee - 0 degrees is vertical - 145
  LegServo(&driver, 4, 363, 180), // Front Right Hip - 270 degrees is forward - 370
  LegServo(&driver, 5, 470, 240), // Front Right Knee - 270 degrees is vertical - 460
  LegServo(&driver, 0, 238,  90), // Back Left Hip
  LegServo(&driver, 1, 136,  30), // Back Left Knee
  LegServo(&driver, 2, 370, 180), // Back Right Hip
  LegServo(&driver, 3, 460, 240), // Back Right Knee
};


void setup() {
  Serial.begin(9600);
  Serial.println("Robot Dog - 8 Servo");

  // start servos
  driver.begin();
  driver.setOscillatorFrequency(25000000);
  driver.setPWMFreq(SERVO_FREQ);

}

void loop() {
  //centerServos();
  stand();
  delay(500);
}
