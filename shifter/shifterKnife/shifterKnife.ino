//aggresive.stag@tamu.edu
//Joseph Gerules 6/13/2017

#define dataPin 4
#define latchPin 5
#define clockPin 6 
#define switchPin 7
byte leds;  //Binary Output for LEDs
//Looping mechanisms defined below
#define wait 50  //Stagnant delay() number
long previousTime = 0;
bool increasing = true;
int ledLength = -1;
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
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}
//------------------------------------------------------------------
//------------------------------------------------------------------

void loop() 
{
  if(digitalRead(switchPin) == HIGH)
  {
    unsigned long currentTime = millis();
    if(currentTime - previousTime > wait) //Checks if the wait time has passed
    {
      previousTime = currentTime; //Resets previous time to current time
      if(increasing)  //If it would normally be in the first for loop
      {
        ledLength++;
        bitSet(leds,ledLength); //Turns LED spot on
      } else {        //If it would normally be in the second for loop
        ledLength--;
        bitClear(leds,ledLength); //Turns LED spot off
      }
       if((ledLength == 8) && (increasing == true))
        increasing = false;
       if((ledLength == -1) && (increasing == false))
        increasing = true;
       updateShiftRegister(leds);
       Serial.println(leds,BIN);
    }
  }
  if(digitalRead(switchPin) == LOW)
  {
    if(leds == 15)
    {
      updateShiftRegister(0);
      delay(150);
      updateShiftRegister(255);
      delay(150);
    }
  }
}
