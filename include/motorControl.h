/************************************************************
 * motorControl.h
 * 
 * Header defining motorControl class
 * 
 * Eric Craaybeek    -    9/17/2025 
 ***********************************************************/

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

class MotorControl {
public:
  MotorControl(uint8_t pinA, uint8_t pinB);
  void init();
  int getEncoderVal() const;

private:

  //Static things to make ISR's work
  static MotorControl* instances[2];
  static uint8_t nextIndex;
  static void ptrISR0();
  static void ptrISR1();

  //Non-static
  void onEncoderChange();
  uint8_t encPinA;
  uint8_t encPinB;
  uint8_t isrID;
  volatile int encValue;

};

#endif // MOTORCONTROL_H