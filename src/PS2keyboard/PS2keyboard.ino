/** 
Título: Programa para imprimir con impresora térmica lo introducido
       con un teclado PS/2 y una pantalla LCD como visualizador
Autor: Ing. Matias Quintana
Fecha: 04/07/2015
**/

#include <SoftwareSerial.h>
#include <PS2Keyboard.h>
#include <LiquidCrystal.h>

const int DataPin = 3;
const int IRQpin =  2;

PS2Keyboard keyboard;
SoftwareSerial Thermal(4, 5);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int zero=0;
int heatTime = 80;
int heatInterval = 255;
char printDensity = 15; 
char printBreakTime = 15;
int i=0; //Ubicación de cursor
char oracion[30];
char impresion[30];

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Thermal.begin(19200); //To write to our new printer
  initPrinter();
  //Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //Print a header to the LCD.
  lcd.print("    NoteTaker");  
}

void initPrinter() {
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

void loop() {
  //Set the cursor to column 0, line 1
  //(Note: line 1 is the second row, since counting begins with 0)
  lcd.setCursor(i, 1);
  //Turn on the blinking cursor
  lcd.blink();
  
  if (keyboard.available()) {
    //Read the next key
    char c = keyboard.read();
    if (c!= NULL) {
      if(i >= 15){
        lcd.scrollDisplayLeft();
        }
        
      if (c == PS2_DELETE){
        if(oracion[16] != NULL ){lcd.scrollDisplayRight();}
        oracion[i-1]=32;
        lcd.print(oracion[i-1]);
        i--;
      }
      
      else{
      oracion[i]=c;
      lcd.print(oracion[i]);
      i++;
      }
    }
    //Check for some of the special keys
    if (c == PS2_ENTER) {
      lcd.clear();
      lcd.print("    NoteTaker");
      // height/width enlarge
      Thermal.write(29); 
      Thermal.write(33);
      Thermal.write(255);  
      Thermal.print(oracion);
      Thermal.write(10);
      
      for(int x=0;x<=i;x++){
        oracion[x]=NULL;
      }
      
      delay(3000);
      i=0;
    } 
  }
}
