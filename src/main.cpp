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
}

void loop() {
  static int lastCounter = 0;

  int currentCounter = motorL.getEncoderVal();
  if (currentCounter != lastCounter) {
    Serial.print("Encoder position: ");
    Serial.println(currentCounter);
    lastCounter = currentCounter;
  }
}