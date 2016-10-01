
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
    for(int i = 5; i < 13; ++i) {
        pinMode(i, INPUT);
    }
}

int notes[8] = {440, 466, 493, 523, 554, 587, 622, 659};
int pitch;

void loop()
{
    bool active = false;
    // Read a value from the FSR

    int j = 0;
    for(int i = 5; i < 13; ++i) {
        active = digitalRead(i);
        if(active) {
            pitch = notes[j];
            break;
        }
        ++j;
    }
    if(!active) {
        noTone(13);
    }
    else {
        tone(13,pitch,20);
    }
    
    // Disable FSR for now...
    /*
    int sensorVal = analogRead(0);

    // Scale value read from between the known minimum and maximum values of
    // the sensor, to a desired range (in Hz)
    pitch = map(sensorVal, 0, 1023, 0, 2000);


    // Output a tone, via digital output 13, to the speaker.
    // The 3rd arguments represents the duration of the tone in milliseconds.

    // Pause for 50 milliseconds
    delay(50);
    */
}
