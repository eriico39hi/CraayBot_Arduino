/************************************************************
 * main.cpp
 * 
 * The main code for the EricBot.
 * Motor control handled by the MotorControl class now.
 * Currently just prints an encoder to the console.
 * 
 * Eric Craaybeek    -    9/17/2025 
 ***********************************************************/

#include <Arduino.h>
#include "motorcontrol.h"

MotorControl motorL(2, 4);
MotorControl motorR(3, 5);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Encoder reading started");

  motorL.init();
  motorR.init();
}

void loop() {
  static int oldEncL = 0;
  static int oldEncR = 0;

  int encL = motorL.getEncoderVal();
  int encR = motorR.getEncoderVal();

  if (oldEncL != encL) {
    Serial.print("Left Encoder position: ");
    Serial.println(encL);
    oldEncL = encL;
  }
  if (oldEncR != encR) {
    Serial.print("Right Encoder position: ");
    Serial.println(encR);
    oldEncR = encR;
  }

}