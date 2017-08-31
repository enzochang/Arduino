#include <Arduino.h>

extern HardwareSerial Serial;

void setup() {
    pinMode(PIN3, OUTPUT);
}

void loop() {
    digitalWrite(PIN3, HIGH);
    delay(200);
    digitalWrite(PIN3, LOW);
    delay(200);            
}