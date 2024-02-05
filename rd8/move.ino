// Leg calibration, movement and walking algorithms

void centerServos() {
  legs[FRONT_LEFT].setDefault();
  legs[FRONT_RIGHT].setDefault();
  legs[BACK_LEFT].setDefault();
  legs[BACK_RIGHT].setDefault();
}

void balanceTest() {
  legs[FRONT_LEFT ].move( 0, 70);
  legs[FRONT_RIGHT].move( 0, 64);
  legs[BACK_LEFT  ].move( 0, 64);
  legs[BACK_RIGHT ].move( 0, 70);
}

void trotInPlace(){
  legs[FRONT_LEFT ].move( 0, 70);
  legs[FRONT_RIGHT].move( 0, 64);
  legs[BACK_LEFT  ].move( 0, 64);
  legs[BACK_RIGHT ].move( 0, 70);
  delay(1000);
  legs[FRONT_LEFT ].move( 0, 64);
  legs[FRONT_RIGHT].move( 0, 70);
  legs[BACK_LEFT  ].move( 0, 70);
  legs[BACK_RIGHT ].move( 0, 64);
  delay(1000);
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

uint8_t sTick = 0;
uint8_t sTicksPerState = 4;
uint8_t sWalkState = 1;
const int8_t sWalkX[] = {-21,  0, 21, 14,  7,  0, -7,-14, -21,  0, 21, 14,  7,  0, -7,-14};
const int8_t sWalkY[] = { 70, 60, 70, 70, 70, 70, 70, 70,  70, 60, 70, 70, 70, 70, 70, 70};
float sCurrentX[4] = {0,0,0,0}, sCurrentY[4] = {70,70,70,70};
float    sPrevX[4] = {0,0,0,0},    sPrevY[4] = {70,70,70,70};
const uint8_t legOrder[4] = {0,3,2,1};
bool sFirstStep = true;
int8_t sDirection = 1; // 1 forward, -1 reverse

void moveStaticWalk() {

  sTick = 3;

  //moving
  for(uint8_t l=0; l<4; l++){
    uint8_t lState = sWalkState + legOrder[l]*2; //offset each leg through the states
  
    if(sTick + 1 == sTicksPerState){ // if this is the last tick just set the targets
      sCurrentX[l] = sWalkX[lState];
      sCurrentY[l] = sWalkY[lState];
      sPrevX[l] = sCurrentX[l];
      sPrevY[l] = sCurrentY[l];
    }
    else{
      sCurrentX[l] += (sWalkX[lState] - sPrevX[l]) / sTicksPerState;
      sCurrentY[l] += (sWalkY[lState] - sPrevY[l]) / sTicksPerState;
    }
    legs[l].move(sCurrentX[l], sCurrentY[l]);
  }
  /*
  if(++sTick == sTicksPerState){ // new state
      sTick = 0;
      sWalkState += sDirection;
      if(sWalkState == 8){ // new cycle
        sWalkState = 0;
      }
      else if(sWalkState == -1){ // new cycle
        sWalkState = 7;
      }
  }
  */
}








