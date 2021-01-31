
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int tiltPin = 8;
int count = 0;

void setup()
{ 
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  pinMode(tiltPin,INPUT);
  digitalWrite(tiltPin, HIGH);
} 
/******************************************/
void loop() 
{  
  int digitalVal = digitalRead(tiltPin);
 
  if(HIGH == digitalVal)
  {
    count++;
    delay(1000);
  }
  
lcd.setCursor(0,1);
lcd.print(count);
}
/**********************************************/
