#include <MIDI.h>  // Add Midi Library

#define LED 7    // Arduino Board LED is on Pin 13

// Create an array to store the state of each piano key (white and black)
bool keysPressed[128] = {false};

// Create an instance of the library with default name, serial port, and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(115200);
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // Set the handler for NOTE ON events
  MIDI.setHandleNoteOff(MyHandleNoteOff); // Set the handler for NOTE OFF events
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
void MyHandleNoteOn(byte channel, byte note, byte velocity) {
  // Check if the note is a black or white piano key (assuming MIDI note numbers)
  if (note >= 21 && note <= 108) {
    keysPressed[note] = true; // Mark the key as pressed in the array
  }
  digitalWrite(LED, true); // Turn LED on
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
void MyHandleNoteOff(byte channel, byte note, byte velocity) {
  // Check if the note is a black or white piano key (assuming MIDI note numbers)
  if (note >= 21 && note <= 108) {
    keysPressed[note] = false; // Mark the key as released in the array
  }
  // Check if all keys are released, and if so, turn off the LED
  bool allKeysReleased = true;
  for (int i = 21; i <= 108; i++) {
    if (keysPressed[i]) {
      allKeysReleased = false;
      break; // Exit the loop as soon as a key is found to be pressed
    }
  }
  if (allKeysReleased) {
    digitalWrite(LED, false); // Turn off the LED
  }
}
