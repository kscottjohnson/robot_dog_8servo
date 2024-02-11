#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <bluefruit.h>

BLEClientUart clientUart;
uint8_t controlMsg[6] = {128,128,128,128,0,0};

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5
#define BUTTON_R 10
#define BUTTON_L 11
#define JOYRX A0
#define JOYRY A1
#define JOYLX A2
#define JOYLY A3
#define BATT_PIN A6

uint8_t mode = 0;
uint8_t lx, ly, rx, ry;
bool buttonA, buttonB, buttonC, buttonR, buttonL;
uint8_t remoteBatt;

//calibration
uint16_t lxMin = 935, lxMax = 0, lyMin = 0, lyMax = 936;
uint16_t rxMin = 936, rxMax = 0, ryMin = 0, ryMax = 935;

unsigned long currentMs;
unsigned long prevMs;

void setup() {
  Serial.begin(115200);
  Serial.println("rd8 remote");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(BUTTON_R, INPUT_PULLUP);
  pinMode(BUTTON_L, INPUT_PULLUP);

  setControls();
  
  setupDisplay();

  startBleScan();

  remoteBatt = readBatt();

  prevMs = millis();
}

void loop() {
  currentMs = millis();
  if(currentMs - prevMs < 50) return;
  prevMs = currentMs;

  if(!digitalRead(BUTTON_A)){
    if(++mode == 2) mode = 0; // cycle mode
    while(!digitalRead(BUTTON_A)){ // pause until button released
      delay(100);
    }
  }

  setControls();

  sendControls();

  remoteBatt = smooth(remoteBatt, readBatt(), 10);

  refreshDisplay();
}





