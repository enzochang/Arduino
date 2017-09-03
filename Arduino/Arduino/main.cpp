#include <Arduino.h>
#include <DHT.h>

DHT dht(2, DHT22);
extern HardwareSerial Serial;
int incomingByte = 0;

void setup() {
    Serial.begin(115200);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    
    dht.begin();
}

void loop() {
    if (Serial.available() > 0) {
        // read the incoming byte
        incomingByte = Serial.read();
        
        // echo it back to sender
        Serial.print("I've received : ");
        Serial.println(incomingByte, DEC);
        digitalWrite(13, HIGH);
    }
    
    digitalWrite(13, LOW);
    delay(100);
}