

/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino:      2, 3
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy 2.0:   5, 6, 7, 8
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
  Modified by Steve Spence <sspence@green-trust.org> September 20013
*/
   
#include <PS2Keyboard.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10); // RX, TX

const int DataPin = 4;
const int IRQpin =  3;

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Keyboard Test:");
}

void loop() {
  
  // mySerial.println("T");
  
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      mySerial.println();
      Serial.println();
    } else if (c == PS2_TAB) {
      mySerial.print("[Tab]");
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      mySerial.print("[ESC]");
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      mySerial.print("[PgDn]");
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      mySerial.print("[PgUp]");
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      mySerial.print("[Left]");
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      mySerial.print("[Right]");
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      mySerial.print("[Up]");
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      mySerial.print("[Down]");
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      mySerial.print("[Del]");
      Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      mySerial.print(c);
      Serial.print(c);
    }
  }
}
