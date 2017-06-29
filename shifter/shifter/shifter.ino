//aggresive.stag@tamu.edu
//Joseph Gerules 6/13/2017

#define dataPin 4
#define latchPin 5
#define clockPin 6 

byte leds;  //Binary Output for LEDs
//Looping mechanisms defined below
#define wait 50  //Stagnant delay() number
long previousTime = 0;
bool increasing = true;
int ledLength = -1;
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
//------------------------------------------------------------------
//------------------------------------------------------------------
void setup() 
{
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}
//------------------------------------------------------------------
//------------------------------------------------------------------
unsigned long count = 0;
void loop() 
{
  if(count == 0)
  {
    Serial.println("Started");
  }
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
     updateShiftRegister();
     //Serial.println(leds,BIN);
  }
  if (currentTime%10000 == 0)  //Prints the amount of loops every 10 seconds
  {
    Serial.println(count);
  }
  count++;
}
