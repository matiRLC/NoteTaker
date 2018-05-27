#include <SoftwareSerial.h>
#include <PS2Keyboard.h> // library to use a PS2Keyboard with Arduino

int DataPin = 4;
int IRQpin =  3;

PS2Keyboard keyboard;

SoftwareSerial Thermal(5, 6); //Se utiliza el D5 como RX y el D6 como TX para la impresora
int zero=0;
int heatTime = 80;
int heatInterval = 255;
char printDensity = 15; 
char printBreakTime = 15;

void setup() 
{
 //Thermal Printer
 Thermal.begin(19200); // to write to our new printer
 initPrinter();
 
 //PS2 Keyboard
 delay(1000);
 keyboard.begin(DataPin,IRQpin);
 Serial.begin(9600);
}
void initPrinter()
{
 //Modify the print speed and heat
 Thermal.write(27);
 Thermal.write(55);
 Thermal.write(7); //Default 64 dots = 8*('7'+1)
 Thermal.write(heatTime); //Default 80 or 800us
 Thermal.write(heatInterval); //Default 2 or 20us
 //Modify the print density and timeout
 Thermal.write(18);
 Thermal.write(35);
 int printSetting = (printDensity<<4) | printBreakTime;
 Thermal.write(printSetting); //Combination of printDensity and printBreakTime
}
void loop()
{
  if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
   
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Thermal.write(27);
      Thermal.write(45); 
      Thermal.write(1);
      Thermal.println();
    }
    
    else {
      // otherwise, just print all normal characters
      Thermal.write(27);
      Thermal.write(45); 
      Thermal.write(1);
      Thermal.println(c);
    }
  }
}
