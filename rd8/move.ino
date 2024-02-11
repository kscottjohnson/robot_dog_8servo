// Leg calibration, movement and walking algorithms

void centerServos() {
  legs[FRONT_LEFT].setDefault();
  legs[FRONT_RIGHT].setDefault();
  legs[BACK_LEFT].setDefault();
  legs[BACK_RIGHT].setDefault();
}

void balanceTest() {
  legs[FRONT_LEFT ].move( 0, 60);
  legs[FRONT_RIGHT].move( 0, 70);
  legs[BACK_LEFT  ].move( 0, 70);
  legs[BACK_RIGHT ].move( 0, 60);
}

void trotInPlace(){
  legs[FRONT_LEFT ].move( 0, 70);
  legs[FRONT_RIGHT].move( 0, 60);
  legs[BACK_LEFT  ].move( 0, 60);
  legs[BACK_RIGHT ].move( 0, 70);
  delay(500);
  legs[FRONT_LEFT ].move( 0, 60);
  legs[FRONT_RIGHT].move( 0, 70);
  legs[BACK_LEFT  ].move( 0, 70);
  legs[BACK_RIGHT ].move( 0, 60);
  delay(500);
}

void stand() {
  for(uint16_t l = 0; l<4; l++){
    legs[l].move(0, 70);
  }
}

void lay() {
  for(uint16_t l = 0; l<4; l++){
    legs[l].move(10, 30);
  }
}

uint8_t sTick = 0;
uint8_t sTicksPerState = 8;
uint8_t sWalkState = 0;
float sCurrentX[4] = {0,0,0,0}, sCurrentY[4] = {70,70,70,70};
float    sPrevX[4] = {0,0,0,0},    sPrevY[4] = {70,70,70,70};
bool sFirstStep = true;
int8_t sDirection = 1; // 1 forward, -1 reverse
uint8_t sLegSpeed = 3; 
uint8_t sWalkStyle = 1; // 0 - walk, 1 - trot
const uint8_t sLegStateOffset[2][4] = { 
  {0,2,1,3}, // walk
  {0,2,2,0}  // trot
};
const int8_t sWalkX[32] = { // pattern repeats to make the offsets loop
  -7, 0, 7, 6, 5, 4, 3, 2, 1, 0,-1,-2,-3,-4,-5,-6,
  -7, 0, 7, 6, 5, 4, 3, 2, 1, 0,-1,-2,-3,-4,-5,-6
};
const int8_t sWalkY[32] = {
  70,45,70,70,70,70,70,70,70,70,70,70,70,70,70,70,
  70,45,70,70,70,70,70,70,70,70,70,70,70,70,70,70
};

void staticWalk() { // defines individual static movement for each leg

  //moving
  for(uint8_t l=0; l<4; l++){
    uint8_t legState = sWalkState + 4 * sLegStateOffset[sWalkStyle][l];
    if(sTick + 1 == sTicksPerState){ // if this is the last tick just set the targets
      sCurrentX[l] = sWalkX[legState]*sLegSpeed;
      sCurrentY[l] = sWalkY[legState];
      sPrevX[l] = sCurrentX[l];
      sPrevY[l] = sCurrentY[l];
    }
    else{
      sCurrentX[l] += (sWalkX[legState]*sLegSpeed - sPrevX[l]) / sTicksPerState;
      sCurrentY[l] += (sWalkY[legState] - sPrevY[l]) / sTicksPerState;
    }
    legs[l].move(sCurrentX[l], sCurrentY[l]);
  }
  
  if(++sTick == sTicksPerState){ // new state
      sTick = 0;
      sWalkState += sDirection;
      if(sWalkState == 16){ // new cycle
        sWalkState = 0;
      }
      else if(sWalkState == -1){ // new cycle
        sWalkState = 15;
      }
  }

}








