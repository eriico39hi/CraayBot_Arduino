/************************************************************
 * main.cpp
 * 
 * The main code for the CraayBot.
 * Motor control handled by the MotorControl class now.
 * Currently just prints an encoder to the console.
 * 
 * Eric Craaybeek    -    9/17/2025 
 ***********************************************************/

#include <Arduino.h>
#include "motorcontrol.h"

//MotorControl constructor args: EncPinA, EncPinB, DirPin1, DirPin2, enaPin
MotorControl motorL(2, 4, 7, 8, 9);
MotorControl motorR(3, 5, 11, 12, 10);

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
  String command = Serial.readStringUntil('\n');
  command.trim();

  int encL = motorL.getEncoderVal();
  int encR = motorR.getEncoderVal();


  if (command == "readencoder"){
    Serial.print("Left Encoder: ");
    Serial.print(encL);
    Serial.print(" Right Encoder: ");
    Serial.println(encR);
  }

  if (command.startsWith("goleft")){
    int speed = 0;
    if (command.length() > 7){
      String speedStr = command.substring(7);
      speed = speedStr.toInt();
    }
    Serial.println(speed);
    motorL.moveMotor(speed, true);
  }

  if (command.startsWith("goright")){
    int speed = 0;
    if (command.length() > 7){
      String speedStr = command.substring(7);
      speed = speedStr.toInt();
    }
    Serial.println(speed);
    motorR.moveMotor(speed, true);
  }

  if (command == "stop"){
    motorL.stopMotor();
    motorR.stopMotor();
  }

}