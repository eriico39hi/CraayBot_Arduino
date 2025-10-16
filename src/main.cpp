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



/*
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') digitalWrite(LED_BUILTIN, HIGH);
    if (c == '0') digitalWrite(LED_BUILTIN, LOW);
  }

}
*/

//MotorControl constructor args: EncPinA, EncPinB, DirPin1, DirPin2, enaPin
MotorControl motorL(2, 4, 7, 8, 9);
MotorControl motorR(3, 5, 11, 12, 10);

void setup() {
  Serial.begin(115200);
  delay(2000);

  motorL.init();
  motorR.init();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  static int oldEncL = 0;
  static int oldEncR = 0;

  int encL = motorL.getEncoderVal();
  int encR = motorR.getEncoderVal();

  Serial.print(encL);
  Serial.print(",");
  Serial.println(encR);

  int speed = 20;

  if (Serial.available()){
    digitalWrite(LED_BUILTIN, HIGH);
    char c = Serial.read();
    if (c == 'f'){
      digitalWrite(LED_BUILTIN, HIGH);
      motorL.moveMotor(speed, true);
      motorR.moveMotor(speed, true);
    } else if (c == 's'){
      digitalWrite(LED_BUILTIN, LOW);
      motorL.stopMotor();
      motorR.stopMotor();
    }
  }

  delay(10);

}
