void setControls() {
  lx = normalizeJoy(analogRead(JOYLX), 0, lxMin, lxMax);
  ly = normalizeJoy(analogRead(JOYLY), 0, lyMin, lyMax);
  rx = normalizeJoy(analogRead(JOYRX), 0, rxMin, rxMax);
  ry = normalizeJoy(analogRead(JOYRY), 0, ryMin, ryMax);

  controlMsg[0] = lx;
  controlMsg[1] = ly;
  controlMsg[2] = rx;
  controlMsg[3] = ry;

  buttonA = !digitalRead(BUTTON_A);
  buttonB = !digitalRead(BUTTON_B);
  buttonC = !digitalRead(BUTTON_C);
  buttonL = !digitalRead(BUTTON_L);
  buttonR = !digitalRead(BUTTON_R);

  controlMsg[4] = 0;
  if(buttonA) controlMsg[4] += 1;
  if(buttonB) controlMsg[4] += 2;
  if(buttonC) controlMsg[4] += 4; 
  if(buttonL) controlMsg[4] += 8;
  if(buttonR) controlMsg[4] += 16;

  controlMsg[5] = mode;
}

uint8_t normalizeJoy(int input, int flip, int min, int max){
  return constrain(map(input, min, max, 0, 255), 1, 255);
}

uint8_t smooth(uint8_t oldValue, uint8_t newValue, uint8_t factor) {
  return (oldValue * factor + newValue) / (factor + 1);
}

uint8_t readBatt() {
  float volts = analogRead(BATT_PIN) * 2.0 * 3.3 / 1024.0;
  return (volts * volts * -2.9487 + volts * 25.0447 - 52.1712) * 200;
}
