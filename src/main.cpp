#include <Arduino.h>
#include <Encoder.h>

const uint8_t encPinA = 2;
const uint8_t encPinB = 3;

Encoder rightEnc(encPinA, encPinB);

long pos = -999;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Encoder reading started");
}

void loop() {
  long newPos = rightEnc.read();
  if (newPos != pos) {
    pos = newPos;
    Serial.print("Encoder position: ");
    Serial.println(pos);
  }
  delay(10);
}