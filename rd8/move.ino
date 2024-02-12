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

void demo() {

  //map left x axis to forward/backward
  float x = map(lx, 0, 255, -30, 30);
  //map left y axis to hight
  float y = map(ly, 0, 255, 30, 96);

  // map right x axis to roll
  float r = map(rx, 0, 255, -30, 30);
  // map right u axis to pitch
  float p = map(ry, 0, 255, -30, 30);

  legs[FRONT_LEFT ].move( x, y-p+r);
  legs[FRONT_RIGHT].move( x, y-p-r);
  legs[BACK_LEFT  ].move( x, y+p+r);
  legs[BACK_RIGHT ].move( x, y+p-r);
}

uint8_t sTick = 0;
uint8_t sTicksPerState = 8;
uint8_t sWalkState = 0;
float sCurrentX[4] = {0,0,0,0}, sCurrentY[4] = {70,70,70,70};
float    sPrevX[4] = {0,0,0,0},    sPrevY[4] = {70,70,70,70};
bool sFirstStep = true;
int8_t sDirection = 1; // 1 forward, -1 reverse
uint8_t sLegSpeed = 3; // multiplier for leg movement
uint8_t sWalkStyle = 0; // 0 - walk, 1 - trot
int8_t sWalkSpeed = 0;
int8_t sMaxWalkSpeed = 8;

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
  
  if(sTick == 0){ // get walk speed at start of walk state
    sWalkSpeed = map(ly, 0, 255, -1 * sMaxWalkSpeed, sMaxWalkSpeed);

    if(sWalkSpeed != 0){
      sTicksPerState =  (float) sMaxWalkSpeed / abs(sWalkSpeed) * 4;
      if(sWalkSpeed > 0){
        sDirection = 1;
      }
      else{ 
        sDirection = -1;
      }
      if(abs(sWalkSpeed) > 4){ // trot if speed >= 5
        sWalkStyle = 1;
      }
      else{ 
        sWalkStyle = 0;
      }
    }
    else {
      sTicksPerState = 16; // for stationary spin
    }

  }
  
  if(sWalkSpeed == 0){

    for(uint8_t l=0; l<4; l++){
      sCurrentX[l] = 0;
      sCurrentY[l] = 70;
      sPrevX[l] = 0;
      sPrevY[l] = 70;

      legs[l].move(sCurrentX[l], sCurrentY[l]);
    }
    sTick = 0;
    sWalkState = 0;
    sDirection = 1;
    sFirstStep = true;
  }
  else{
    //moving
    //Serial.print(sWalkState);Serial.print(" ");Serial.println(sTick);
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
      if(sFirstStep && legState < 9){
        // hack to make non-lifting leg not go forward when starting
        sCurrentX[l] = 0; 
        sPrevX[l] = 0;
      }
      legs[l].move(sCurrentX[l], sCurrentY[l]);
    }

    if(++sTick == sTicksPerState){ // new state
      sTick = 0;
      sWalkState += sDirection;
      sFirstStep = false;
      if(sWalkState == 16){ // new cycle
        sWalkState = 0;
      }
      else if(sWalkState == 255){ // new cycle
        sWalkState = 15;
      }
    }
  }

  

}








