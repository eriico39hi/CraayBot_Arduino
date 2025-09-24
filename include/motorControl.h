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
  MotorControl(uint8_t inEncPinA, uint8_t inEncPinB, uint8_t inDirPin1, uint8_t inDirPin2, uint8_t inEnaPin);
  void init();
  int getEncoderVal() const;
  void MotorControl::moveMotor(uint8_t speed, bool fwdDirCtl);
  void MotorControl::stopMotor();

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
  uint8_t dirPin1;
  uint8_t dirPin2;
  uint8_t enaPin;
  uint8_t isrID;
  volatile int encValue;

};

#endif // MOTORCONTROL_H