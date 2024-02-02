#ifndef LegServo_h
#define LegServo_h

class LegServo {
  public:
    LegServo(Adafruit_PWMServoDriver* driver, int num, int defaultPWM, 
      int defaultAngle);
    void setDefault();
    void setAngle(float ang);
  private:
    Adafruit_PWMServoDriver* _driver;
    int _num;
    int _defaultPWM;
    int _defaultAngle;
    void _setPWM(int pwm);
};

LegServo::LegServo(Adafruit_PWMServoDriver* driver, int num, int defaultPWM, 
  int defaultAngle){
  
  _driver = driver;
  _num = num;
  _defaultPWM = defaultPWM;
  _defaultAngle = defaultAngle;
}

void LegServo::_setPWM(int pwm){
  this->_driver->setPWM(this->_num, 0, pwm);
}

void LegServo::setDefault(){
  this->_setPWM(this->_defaultPWM);
}

void LegServo::setAngle(float ang){
  float pwm = (ang - this->_defaultAngle) * 1.5 + this->_defaultPWM;
  this->_driver->setPWM(this->_num, 0, pwm);
}

class Leg {
  public:
    Leg(LegServo* hipServo, LegServo* kneeServo, bool reverseLeg);
    LegServo* hip;
    LegServo* knee;
    void setDefault();
    void setAngles(float h, float k);
    bool isReversed();
  private:
    bool _reverseLeg;
};

Leg::Leg(LegServo* hipServo, LegServo* kneeServo, bool reverseLeg){
  hip = hipServo;
  knee = kneeServo;
  _reverseLeg = reverseLeg;
}

void Leg::setDefault(){
  this->hip->setDefault();
  this->knee->setDefault();
}


float adjacentAngle(float a) {
  // gets the adjacent angle in a specified quadrilateral with sides 24,18,18,18

  return (
    (
      acos((648.0-648.0*cos(a*DEG_TO_RAD))/(36.0*sqrt(648.0-648.0*cos(a*DEG_TO_RAD)))) +
      acos((396.0-648.0*cos(a*DEG_TO_RAD))/(36.0*sqrt(648.0-648.0*cos(a*DEG_TO_RAD))))
    )
    *RAD_TO_DEG
  );
}

void Leg::setAngles(float h, float k){
  //Serial.print("setting angles "); 
  //Serial.print(h); Serial.print(" "); 
  //Serial.println(k);

  float k2 = adjacentAngle(-1 * (k + h - 315)) - 45;

  //Serial.print("servo angles "); 
  //Serial.print(h); Serial.print(" "); 
  //Serial.println(k2);

  if(this->isReversed()){
    this->hip->setAngle(270-h); 
    this->knee->setAngle(270-k2);
  }
  else{
    this->hip->setAngle(h); 
    this->knee->setAngle(k2);
  }
}

bool Leg::isReversed() {
  return this->_reverseLeg;
}

#endif
