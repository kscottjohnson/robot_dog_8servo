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

void Leg::setAngles(float h, float k){
  if(this->isReversed()){
    this->hip->setAngle(270-h); 
    this->knee->setAngle(270-k);
  }
  else{
    this->hip->setAngle(h); 
    this->knee->setAngle(k);
  }
}

bool Leg::isReversed() {
  return this->_reverseLeg;
}

#endif
