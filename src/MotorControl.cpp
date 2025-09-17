/************************************************************
 * motorControl.cpp
 * 
 * Class to handle a DC motor controlled by L298N with
 * a incremental rotary encoder
 * 
 * Eric Craaybeek    -    9/17/2025 
 ***********************************************************/


#include "motorcontrol.h"

//During initialization of the class, init some statics
MotorControl* MotorControl::instances[2] = {nullptr, nullptr};
uint8_t MotorControl::nextIndex = 0;

//Constructor: Initializes pin #'s and sets starting encoder val to 1
MotorControl::MotorControl(uint8_t pinA, uint8_t pinB)
  : encPinA(pinA), encPinB(pinB), encValue(0) {
  if (nextIndex < 2){
    isrID = nextIndex;
    nextIndex++;
  } else {
    //error, can't support more than 2 ISR's
  }
}

//Initialize Motor Object: sets pinModes on arduino, sets up the interrupt function
void MotorControl::init() {
  pinMode(encPinA, INPUT);
  pinMode(encPinB, INPUT);

  if (isrID < 2){
    instances[isrID] = this;
  }
  
  if (isrID == 0){
    attachInterrupt(digitalPinToInterrupt(encPinA), ptrISR0, CHANGE);
  } else if (isrID == 1) {
    attachInterrupt(digitalPinToInterrupt(encPinA), ptrISR0, CHANGE);
  }
}

//Read-only access to encoder value
int MotorControl::getEncoderVal() const {
  return encValue;
}

//Odd workaround to allow ISR's in a class
void MotorControl::ptrISR0() {
    instances[0]->onEncoderChange();
}
void MotorControl::ptrISR1() {
    instances[1]->onEncoderChange();
}

//The actual ISR for reading encoder (pointed to from static one)
void MotorControl::onEncoderChange() {
  int stateA = digitalRead(encPinA);
  int stateB = digitalRead(encPinB);
  if (stateA == stateB) {
    encValue++;
  } else {
    encValue--;
  }
}