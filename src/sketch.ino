
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
}

void loop()
{
    // Read a value from the FSR
    int sensorVal = analogRead(0);

    // Scale value read from between the known minimum and maximum values of
    // the sensor, to a desired range (in Hz)
    int pitch = map(sensorVal, 0, 1023, 0, 8000);

    // Output a tone, via digital output 8, to the speaker.
    // The 3rd arguments represents the duration of the tone in milliseconds.
    tone(8,pitch,20);

    // Pause for 50 milliseconds
    delay(50);
}
