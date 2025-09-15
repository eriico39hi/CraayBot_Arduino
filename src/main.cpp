#include <Arduino.h>

const uint8_t encPinA = 2;
const uint8_t encPinB = 4;

int counter = 0; 

void onEncoderChange() {

  int stateA = digitalRead(encPinA);
  int stateB = digitalRead(encPinB);

  if (stateA == stateB) {
    counter ++;
  } else {
    counter --;
  }
}

void setup() {

  pinMode (encPinA,INPUT);
  pinMode (encPinB,INPUT);
  Serial.begin(115200);

  delay(1000);
  Serial.println("Encoder reading started");

  attachInterrupt(digitalPinToInterrupt(encPinA), onEncoderChange, CHANGE);
}

void loop() {

  static int lastCounter = 0;

  if (counter != lastCounter) {
    Serial.print("Encoder position: ");
    Serial.println(counter);
    lastCounter = counter;
  }

}