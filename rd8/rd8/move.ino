// Leg calibration, movement and walking algorithms

void centerServos() {
  legs[FRONT_LEFT].setDefault();
  legs[FRONT_RIGHT].setDefault();
  legs[BACK_LEFT].setDefault();
  legs[BACK_RIGHT].setDefault();
}

void stand() {
  for(uint16_t l = 0; l<4; l++){
    legs[l].setAngles(135, 70);
  }
}

void lay() {
  for(uint16_t l = 0; l<4; l++){
    legs[l].setAngles(148, 26);
  }
}