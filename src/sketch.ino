
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

// Class to handle output of a melody on a note by note basis and in full.
class TunePlayer {
    private:
        // Arrays of values relating to the pitch, order and duration (in quavers) of the melody.
        const int tetrisNotes[8] = {1760, 1975, 2093, 2349, 2637, 2793, 3135, 3520};
        const int tetrisOrder[38] = {4, 1, 2, 3, 2, 1, 0, 0, 2, 4, 3, 2, 1, 1, 2, 3, 4, 2, 0, 0, 3, 5, 7, 6, 5, 4, 2, 4, 3, 2, 1, 1, 2, 3, 4, 2, 0, 0};
        const int tetrisDurations[38] = {2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 4, 3, 1, 2, 1, 1, 3, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 3};
        // Integer to store the current position in the melody.
        int tunePosition = 0;
        // Boolean value to store the state of the individual note-playing button.
        bool buttonPressed = false;

    public:
        void playTune() {
            // This was created out of misreading the bonus step... Enjoy!
            // Declare static arrays holding frequency, note duration and note order data for a tune.
            // Iterate over arrays, playing notes with durations specified as multiples of quavers at 144bpm
            for(int i = 0; i < 38; ++i)
            {
                tone(13,tetrisNotes[tetrisOrder[i]],tetrisDurations[i]*206);
                delay(tetrisDurations[i]*206);
            }
        }

        void playTuneNote() {
            // Begin playing a note from the melody if one is not already playing.
            if(!buttonPressed) {
                tone(13,tetrisNotes[tetrisOrder[tunePosition]]);
                // Increment the position ready for the next note to be played
                incrementPosition();
                // Set the button state as true so that further calls to the
                // function from the current press do nothing until it is
                // released.
                buttonPressed = true;
            }
        }

        void buttonInactive() {
            // Public method for declaring the button as released.
            buttonPressed = false;
        }

        int incrementPosition() {
            // Mthod for incrementing the tune position without exceeding the
            // number of positions available.
            ++tunePosition;
            if(tunePosition > 37) {
                tunePosition = 0;
            }
            return tunePosition;
        }
};

// Define integer frequencies in hertz from A (440hz) chromatically.
int notes[8] = {440, 466, 493, 523, 554, 587, 622, 659};
// Define a a global variable for pitch.
int pitch;


// Create a global player object instance.
TunePlayer player = TunePlayer();

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
    // Switch allows for easy overwriting of buton's default functionality.
    switch(j) {
        case 7:
            // Special case to play tune with button 7.
            player.playTune();
            break;
        case 6:
            // Special case to play tune on a per note basis with button 6.
            player.playTuneNote();
            break;
        case 8:
            // If no note is active then silence instrument.
            noTone(13);
            // Set tune button as inactive ready for next note.
            player.buttonInactive();
            break;
        default:
            // default action to output a tone for a button
            // Get integer value from FSR in range 0-1023
            int sensorVal = analogRead(0);

            // Calculate the offset 5% of the bend.
            int bend = round(pitch / 100.0 * 5.0);

            // Map values from the FSR to the pitch -5% to the pitch +5%
            pitch = map(sensorVal, 0, 1023, pitch-bend, pitch+bend);

            // Generate tone based on pitch +/- bend.
            tone(13,pitch);
            player.buttonInactive();
            break;
    }
}
