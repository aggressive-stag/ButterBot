#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

void setup()

{

// set up the LCD’s number of columns and rows:

lcd.begin(16, 2);

}

 
int x = 0;
void loop()

{
x++;
lcd.print(x);
delay(1000);
lcd.scrollDisplayLeft();//shifting data on LCD

//lcd.setCursor(0, 0);// set the cursor to column 0, line1

}
