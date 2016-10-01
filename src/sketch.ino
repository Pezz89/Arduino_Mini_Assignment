
// analog-plot
// 
// Read analog values from A0 and A1 and print them to serial port.
//
// electronut.in

#include "Arduino.h"

void setup()
{
    // Communication with the computer is not needed in this project.
    //Serial.begin(9600); 
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);
    pinMode(12, INPUT);
}

void loop()
{
    // Read a value from the FSR
    int buttonVal5 = digitalRead(5);
    int buttonVal6 = digitalRead(6);
    int buttonVal7 = digitalRead(7);
    int buttonVal8 = digitalRead(8);
    int buttonVal9 = digitalRead(9);
    int buttonVal10 = digitalRead(10);
    int buttonVal11 = digitalRead(11);
    int buttonVal12 = digitalRead(12);
    int sensorVal = analogRead(0);

    // Scale value read from between the known minimum and maximum values of
    // the sensor, to a desired range (in Hz)
    int pitch = map(sensorVal, 0, 1023, 0, 2000);

    if(buttonVal5 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal6 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal7 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal8 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal9 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal10 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal11 == HIGH) {
        pitch += 1000;
    }
    if(buttonVal12 == HIGH) {
        pitch += 1000;
    }

    // Output a tone, via digital output 13, to the speaker.
    // The 3rd arguments represents the duration of the tone in milliseconds.
    tone(13,pitch,20);

    // Pause for 50 milliseconds
    delay(50);
}
