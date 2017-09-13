#include <Arduino.h>
#include <DHT.h>
#include "SoftwareSerial.h"
#include "Temperature.h"

void serialFloatPrint(float f);

DHT dht(2, DHT11);
SoftwareSerial Serial2(3, 4); // RX, TX


byte incomingByte;
char b_header = 0x7e;
char tempCtl = 0x7d;
char humidCtl = 0x7c;
char bothCtl = 0x7b;

void setup() {
    Temperature dp = Temperature();

    Serial2.begin(115200);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    dht.begin();
}

void loop() {
    float h = 0.0f;
    float t = 0.0f;

    //Serialize data.

    //for (char c_Index = sizeof ( float) - 1; c_Index >= 0; Serial2.write(c_Data[ c_Index-- ]));
    if (Serial2.available() > 0) {
        // read the incoming byte
        incomingByte = Serial2.read();
        
        if (incomingByte == tempCtl) {
            t = dht.readTemperature();
        }

        if (incomingByte == humidCtl) {
            h = dht.readHumidity();
        }

        if (incomingByte == bothCtl) {
            t = dht.readTemperature();
            h = dht.readHumidity();
        }

        float f_Temp = t;
        float f_Humidity = h;

        Serial2.write(b_header);
        Serial2.write(incomingByte);
        
        char *c_Temp = (char*) &f_Temp;
        for (char c_Index = 0; c_Index < sizeof ( float); Serial2.write(c_Temp[ c_Index++ ]));

        char *c_Humid = (char*) &f_Humidity;
        for (char c_Index = 0; c_Index < sizeof ( float); Serial2.write(c_Humid[ c_Index++ ]));
    }

    // digitalWrite(13, LOW);
    delay(200);
}