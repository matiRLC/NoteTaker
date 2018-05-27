/*
 Example 38.2 - Sparkfun Thermal Printer Test II (COM-10438)
 http://tronixstuff.com/tutorials > chapter 38
 Based on code by Nathan Seidle of Spark Fun Electronics 2011
 */
#include <SoftwareSerial.h>
SoftwareSerial Thermal(4, 5);
int zero=0;
int heatTime = 80;
int heatInterval = 255;
char printDensity = 15; 
char printBreakTime = 15;
void setup() 
{
 Serial.begin(57600); // for debug info to serial monitor
 Thermal.begin(19200); // to write to our new printer
 initPrinter();
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
 Serial.println();
 Serial.println("Printer ready"); 
}
void loop()
{
 // underline - one pixel
 Thermal.write(27);
 Thermal.write(45); 
 Thermal.write(1);
 Thermal.println("Underline - thin");
 Thermal.println("01234567890123456789012345678901"); 
 Thermal.write(10);
// underline - two pixels
 Thermal.write(27); 
 Thermal.write(45);
 Thermal.write(2); 
 Thermal.println("Underline - thick");
 Thermal.println("01234567890123456789012345678901"); 
 Thermal.write(10);
// turn off underline
 Thermal.write(27); 
 Thermal.write(45);
 Thermal.write(zero);
 delay(3000);
 Thermal.write(10);
// bold text on
 Thermal.write(27); 
 Thermal.write(32);
 Thermal.write(1);
 Thermal.println(" #### Bold text #### ");
 Thermal.println("01234567890123456789012345678901"); 
 delay(3000);
// bold text off
 Thermal.write(27); 
 Thermal.write(32);
 Thermal.write(zero);
 Thermal.write(10); //Sends the LF to the printer, advances the paper
 delay(3000);
// height/width enlarge
 Thermal.write(29); 
 Thermal.write(33);
 Thermal.write(255);
 Thermal.println("ABCDEF");
 Thermal.println("012345"); 
 delay(3000);
// back to normal
 Thermal.write(29); 
 Thermal.write(33);
 Thermal.write(zero);
 delay(3000);
Thermal.write(10);
 Thermal.println("Back to normal...");
 Thermal.write(10);
 Thermal.write(10); 
 do { } while (1>0); // do nothing
}
