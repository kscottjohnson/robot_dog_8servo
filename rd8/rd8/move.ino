// Leg calibration, movement and walking algorithms

void centerServos() {
  legs[FRONT_LEFT].setDefault();
  legs[FRONT_RIGHT].setDefault();
  legs[BACK_LEFT].setDefault();
  legs[BACK_RIGHT].setDefault();
}

void stand() {
  for(uint16_t l = 0; l<4; l++){
    //legs[l].setAngles(135, 90); 
    legs[l].move(0, 70);
  }
}

void lay() {
  for(uint16_t l = 0; l<4; l++){
    //legs[l].setAngles(148, 30);
    legs[l].move(10, 30);
  }
}

const int8_t sWalkX[] = {-15,  0, 15, 10,  5,  0, -5,-10, -15,  0, 15, 10,  5,  0, -5,-10};
const int8_t sWalkY[] = { 70, 66, 70, 70, 70, 70, 70, 70,  70, 66, 70, 70, 70, 70, 70, 70};

void moveStaticWalk() {



}