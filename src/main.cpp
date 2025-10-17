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
#include <motorControl.h>

//MotorControl constructor args: EncPinA, EncPinB, DirPin1, DirPin2, enaPin, negateEnc
MotorControl motorL(2, 4, 7, 8, 9, false);
MotorControl motorR(3, 5, 11, 12, 10, true);

void setup() {
  Serial.begin(115200);
  delay(2000);

  motorL.init();
  motorR.init();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
}

int leftSpeed = 0;
int rightSpeed = 0;

void loop() {
  static int oldEncL = 0;
  static int oldEncR = 0;

  int encL = motorL.getEncoderVal();
  int encR = motorR.getEncoderVal();

  Serial.print(encL);
  Serial.print(",");
  Serial.println(encR);

  if (Serial.available()){
    String rcvStr = Serial.readStringUntil('\n');
    rcvStr.trim();

    int commaLoc = rcvStr.indexOf(',');
    String leftRcvStr = rcvStr.substring(0,commaLoc); 
    String rightRcvStr = rcvStr.substring(commaLoc+1);

    leftSpeed = leftRcvStr.toInt();
    rightSpeed = rightRcvStr.toInt();

  }

  if (leftSpeed != 0){
    motorL.moveMotor(leftSpeed);
  } else if (leftSpeed == 0){
    motorL.stopMotor();
  }

  if (rightSpeed != 0){
    motorR.moveMotor(rightSpeed);
  } else if (rightSpeed == 0){
    motorR.stopMotor();
  }

  delay(10);

}
