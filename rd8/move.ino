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
uint8_t sTicksPerState = 3;
uint8_t sWalkState = 0;
float sCurrentX[4] = {0,0,0,0}, sCurrentY[4] = {70,70,70,70};
float    sPrevX[4] = {0,0,0,0},    sPrevY[4] = {70,70,70,70};
bool sFirstStep = true;
int8_t sDirection = 1; // 1 forward, -1 reverse

// 16 states
const int8_t sWalkX4[4][16] = {
  {-21,  0, 21, 18, 15, 12,  9,  6,  3,  0, -3, -6, -9,-12,-15,-18}, //1
  {  3,  0, -3, -6, -9,-12,-15,-18,-21,  0, 21, 18, 15, 12,  9,  6}, //3
  { 15, 12,  9,  6,  3,  0, -3, -6, -9,-12,-15,-18,-21,  0, 21, 18}, //4
  { -9,-12,-15,-18,-21,  0, 21, 18, 15, 12,  9,  6,  3,  0, -3, -6}  //2
};

const int8_t sWalkY4[4][16] = {
  { 70, 60, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70},
  { 70, 70, 70, 70, 70, 70, 70, 70, 70, 60, 70, 70, 70, 70, 70, 70},
  { 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 60, 70, 70},
  { 70, 70, 70, 70, 70, 60, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70}
};

void staticWalk4() { // defines individual static movement for each leg

  //sTick = 3;
  //sWalkState = 7;

  //moving
  for(uint8_t l=0; l<4; l++){
    
    if(sTick + 1 == sTicksPerState){ // if this is the last tick just set the targets
      sCurrentX[l] = sWalkX4[l][sWalkState];
      sCurrentY[l] = sWalkY4[l][sWalkState];
      sPrevX[l] = sCurrentX[l];
      sPrevY[l] = sCurrentY[l];
    }
    else{
      sCurrentX[l] += (sWalkX4[l][sWalkState] - sPrevX[l]) / sTicksPerState;
      sCurrentY[l] += (sWalkY4[l][sWalkState] - sPrevY[l]) / sTicksPerState;
    }
    legs[l].move(sCurrentX[l], sCurrentY[l]);
  }
  
  ///*
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
  //*/
}








