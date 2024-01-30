// Leg calibration, movement and walking algorithms

void centerServos() {
  //legs[FRONT_RIGHT].setDefault();
  //legs[FRONT_LEFT].setDefault();
  //legs[BACK_RIGHT].setDefault();
  //legs[BACK_LEFT].setDefault();

  for(uint16_t s = 0; s < 8; s++)
    servos[s].setDefault();
}

void stand() {

  servos[0].setAngle(135);
  servos[1].setAngle(70);
  servos[2].setAngle(135);
  servos[3].setAngle(200);
  servos[4].setAngle(135);
  servos[5].setAngle(70);
  servos[6].setAngle(135);
  servos[7].setAngle(200);
}