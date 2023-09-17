/*
  Author: Lauren Crist
  Project: Keypad Project
  Date: 2/28/19
  Description: This Arduino code controls a keypad-based lock system. When the correct code is entered on the keypad, it unlocks a door by lighting a green LED. An incorrect code triggers a red LED to indicate an invalid entry.
*/

#include <Keypad.h>

// Pin assignments for LEDs
int REDLED = 10;
int GREENLED = 11;

// Code to unlock the door
char* ourCode = "0280";
int currentPosition = 0;

// Keypad setup
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'#','0','*', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
}

void loop() {
  int i;
  char key = keypad.getKey();

  if (key != 0) {
    for (i = 0; i <= currentPosition; i++) {
      // Do nothing; iterate to the current position
    }
  }
  
  if (key == ourCode[currentPosition]) {
    currentPosition++;

    if (currentPosition == 4) { // Check if the entire code has been entered
      unlockDoor();
      currentPosition = 0; // Reset the code entry position
    }
  } else {
    invalidCode();
    currentPosition = 0; // Reset the code entry position
  }
}

void invalidCode() {
  digitalWrite(REDLED, HIGH);
  delay(5000);
  digitalWrite(REDLED, LOW);
}

void unlockDoor() {
  digitalWrite(GREENLED, HIGH);
  delay(5000);
  digitalWrite(GREENLED, LOW);
}
