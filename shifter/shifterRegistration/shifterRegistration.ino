//aggresive.stag@tamu.edu
//Joseph Gerules 6/13/2017

#include "vectorCheat.h"
#define dataPin 4
#define latchPin 5
#define clockPin 6 
#define switchPinRight 7
#define switchLeft 8
#define switchRight 10
#define switchPinLeft 11
byte leds = 1;  //Binary Output for LEDs
int ledLength = 0;
bool blinker;
vectorCheat object;

void updateShiftRegister(byte binaryNum)
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, binaryNum);
   digitalWrite(latchPin, HIGH);
}
//------------------------------------------------------------------
//------------------------------------------------------------------
void setup() 
{
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(switchPinRight, INPUT_PULLUP);
  pinMode(switchLeft, INPUT_PULLUP);
  pinMode(switchRight, INPUT_PULLUP);
  pinMode(switchPinLeft, INPUT_PULLUP);
  Serial.begin(9600);
}
//------------------------------------------------------------------
//------------------------------------------------------------------

void loop() 
{
  if(blinker == true)
  {
    byte tempLeds = leds;                 //Turns light on and off with a temp so that
    bitSet(tempLeds,ledLength);           //it doesn't affect your actual bit. MAKES
    updateShiftRegister(tempLeds);        // S P O T V I S I B L E ! ! !
    delay(50);
    bitClear(tempLeds,ledLength);
    updateShiftRegister(tempLeds);
    delay(50);
  }
  
  if((digitalRead(switchLeft) == LOW) && (ledLength != 7))   //Moves up the line && turns led on
  {
    ledLength++;
    bitSet(leds,ledLength);
    delay(300);
  }
  if(digitalRead(switchRight) == LOW && (ledLength != 0))   //Moves down the line && turns led on
  {
     ledLength--;
     bitSet(leds,ledLength);
     delay(300);
  }
  if((digitalRead(switchPinLeft) == LOW))     //Turns blinker on off
  {
    if(blinker == true)
      blinker = false;
    else
      blinker = true;
    delay(300);
    object.v.push_back(leds);             //Vector Cheat is used to store and print
    int tempLength = object.v.size();
    for(int i = 0; i < tempLength; i++)       //Serial prints inside here
    {
      int tempSpot = object.v[i];
      Serial.print("Slot::\t");
      Serial.print(i);                        //Prints what spot in the list it is
      Serial.print("\tValue::\t");
      Serial.println(leds,BIN);               //Prints BIN value of spot
      updateShiftRegister(tempSpot);
      delay(500);
    }
    updateShiftRegister(255);
    delay(200);
    updateShiftRegister(leds);
  }
  if((digitalRead(switchPinRight) == LOW))    //Clears bit/turns current light off
  {
    if(bitRead(leds,ledLength) == 0)
      bitSet(leds,ledLength);
    else
     bitClear(leds,ledLength); 
    delay(300);
  }
  updateShiftRegister(leds);
}
