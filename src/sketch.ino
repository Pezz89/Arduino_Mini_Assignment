
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
    // Set digital pins as inputs ready to read incoming data from buttons.
    for(int i = 5; i < 13; ++i) {
        pinMode(i, INPUT);
    }
}

// Define integer frequencies in hertz from A (440hz) chromatically.
int notes[8] = {440, 466, 493, 523, 554, 587, 622, 659};
// Define a a global variable for pitch.
int pitch;

void loop()
{
    // Declare a bool for testing if button is active.
    bool active = false;

    // For each button index, check if button is currently pressed...
    int j = 0;
    for(int i = 5; i < 13; ++i) {
        active = digitalRead(i);
        // If it is, set the output pitch to the frequency stored in the notes
        // variable at the index of the button pressed
        if(active) {
            pitch = notes[j];
            // break out of for loop as further iterations are not neccesary.
            break;
        }
        // If note isn't active then increment index counter.
        ++j;
    }
    // If no note is active then silence instrument.
    if(!active) {
        noTone(13);
    }
    // Otherwise, output a tone.
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
