/* Arduino program for the Larger than Life Piano - a House of General Science project.
 * Written for the Fall 2021 Rochester Maker Faire.
 * Written by Will Ebmeyer - 11/18/2021
 * 
 * This program reads from pins 31-44 on an Arduino Mega to determine whether a key
 * has been pressed or released on the piano.  If it detects such an event, it sends
 * a signal over serial to a connected computer in the format "keyDown|[KEY]" or
 * "keyUp|[KEY]."
 * The pins should be connected to the piano keys—which themselves must be connected
 * to GROUND (NOT VOLTAGE, IT DOESN'T WORK WITH VOLTAGE).
*/

#define KEY_PIN_START 31
#define KEY_COUNT 13

bool key_states[KEY_COUNT];

void setup() {
  // Set up the serial
  Serial.begin(9600);

  // Get the input pins set up
  for (int i = 0; i < KEY_COUNT; i++) {
    pinMode(KEY_PIN_START+i, INPUT_PULLUP);
  }
}

void loop() {
  // Read from keyboard and send keyDown/keyUp events if applicable
  for (int i = 0; i < KEY_COUNT; i++) {
    // Read state of key
    bool key = digitalRead(KEY_PIN_START+i);

    //Serial.print(key); // Print all key states - used for debugging purposes

    // Compare key with last available record of key
    if (key_states[i] != key) {
      // State changed, send event signal over serial
      if (key == true) {
        Serial.print("keyUp|");
        Serial.print(i);
        Serial.print("\n");
      } else {
        Serial.print("keyDown|");
        Serial.print(i);
        Serial.print("\n");
      }
      key_states[i] = key;
    }
  }
  //Serial.print("\n"); // Only enable this if you've reenabled the above "Serial.print(key);" line.  This, too, is for debugging purspoes

  // Sleep to reduce strain on the Arduino
  delay(10);
}
