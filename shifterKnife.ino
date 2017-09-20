//aggresive.stag@tamu.edu
//Joseph Gerules 9/13/2017
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
int altLeds = 0;
//------------------------------------------------------------------
//------------------------------------------------------------------
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
template <class T> bool quickDelay(T w)
{
  unsigned long currentTime = millis();
  if((currentTime - previousTime) > w)
  {
    previousTime = currentTime;
    return true;
  }
  else
    return false;
}
//------------------------------------------------------------------
//------------------------------------------------------------------
void loop() 
{
  if(digitalRead(switchPin) == HIGH)  //IF SWITCH != PUSHED
  {
    if(quickDelay(wait)) //OPTIMIZED DELAY
    {
      if(increasing)  //GAINING LIGHTS
      {
        ledLength++;
        bitSet(leds,ledLength);   //TURN LED SPOT ON
      } else {        //LOSING LIGHTS
        ledLength--;
        bitClear(leds,ledLength); //TURN LED SPOT OFF
      }
       if((ledLength == 8) && (increasing == true))
        increasing = false;
       if((ledLength == -1) && (increasing == false))
        increasing = true;
       updateShiftRegister(leds);
       Serial.println(leds,BIN);  //MONITORING(NOT NEEDED)
    }
  }
  
  if(digitalRead(switchPin) == LOW) //IF SWITCH = PUSHED
  {
    if(leds == 15) //Middle LED
    {
      if(quickDelay(10) && (altLeds !=0))
      {
        altLeds = 0; updateShiftRegister(altLeds);
        Serial.println("W I N N E R - * - * - W I N N E R - * - * - WINNER");
      }
      else if(quickDelay(10) && (altLeds == 0))
      {
        altLeds = 255; updateShiftRegister(altLeds);
      }
    }
  }
}
