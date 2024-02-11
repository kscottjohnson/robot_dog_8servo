#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <bluefruit.h>

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
  LegServo(&driver, 7, 126,  22), // Front Left Knee - 0 degrees is vertical - 145
  LegServo(&driver, 4, 363, 180), // Front Right Hip - 270 degrees is forward - 370
  LegServo(&driver, 5, 470, 248), // Front Right Knee - 270 degrees is vertical - 460
  LegServo(&driver, 0, 238,  90), // Back Left Hip
  LegServo(&driver, 1, 136,  22), // Back Left Knee
  LegServo(&driver, 2, 370, 180), // Back Right Hip
  LegServo(&driver, 3, 459, 248), // Back Right Knee
};

Leg legs[4] = {
  Leg(&servos[0], &servos[1], false, 2), // Front Left
  Leg(&servos[2], &servos[3], true,  2), // Front Right
  Leg(&servos[4], &servos[5], false, 2), // Back Left
  Leg(&servos[6], &servos[7], true,  2), // Back Right
};

// Bluetooth
BLEUart bleuart;
uint8_t controlMsg[6] = {128,128,128,128,0,0};
uint8_t rx, ry, lx, ly;
bool buttonAR, buttonBR, buttonCR, buttonR, buttonL;
uint8_t mode = 0;

#define CLOCK_CYCLE 5
unsigned long currentMs;
unsigned long prevMs;
unsigned long connectedMs;

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
  delay(100);

  startBleAdv();

  delay(500);

  prevMs = millis();
}

void loop() {
  currentMs = millis();
  if((currentMs - prevMs) < CLOCK_CYCLE) return;
  prevMs = currentMs;

  if(! Bluefruit.Periph.connected()){
    Serial.println("Not Connected");
    stand();
    delay(1000);
    return;
  }
  if((currentMs - connectedMs) < 1000){ // wait a second after connecting
    return;
  }

  //centerServos();
  //stand();
  //lay();
  //balanceTest();
  //trotInPlace();
  //staticWalk();

  //Serial.print("Mode "); Serial.print(mode);
  if(mode == 0) stand();
  else if(mode == 1) demo();
  else if(mode == 2) staticWalk();
  else stand();

}
