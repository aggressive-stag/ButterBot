int buttonApin = 13;
int buttonBpin = 12;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int bright = 255; //MAX light value
int delayTime = 500; //time between light changes
int path = -1; //Determines which path the main loop takes
int freeLance = 2; //Free random variable later(acts like counter)

void setup() 
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);  
}
void setColor(int red, int green, int blue) //function call to change led color
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void colorCycle(int cycle)
{
  switch(cycle){
    case 0:
    setColor(148, 0, 211);  // indigo
    delay(delayTime);
    break;

    case 11:
    case 1:
    setColor(75, bright, 130);  // dark indigo
    delay(delayTime);
    break;
    
    case 10:
    case 2:
    setColor(0, 0, 255);  // blue
    delay(delayTime);
    break;
    
    case 9:
    case 3:
    setColor(0, bright, 0);  // green
    delay(delayTime);
    break;

    case 8:
    case 4:
    setColor(bright, bright, 0);  // yellow
    delay(delayTime);
    break;

    case 7:
    case 5:
    setColor(bright, 127, 0);  // orange
    delay(delayTime);
    break;

    case 6:
    setColor(bright, 0, 0);  // red
    delay(delayTime);
    
  }
}

void loop() 
{
  if (digitalRead(buttonApin) == LOW) //If higher button is pushed
  {
    path = 0;
    if(delayTime != 100)
      delayTime = delayTime - 100;
  }
  if (digitalRead(buttonBpin) == LOW) //If lower button is pushed
  {
    path = 1;
    if(delayTime != 1000)
      delayTime = delayTime + 100;
  }
  
  if(path == 0)
  {
    colorCycle(freeLance);
    freeLance++;
    if(freeLance == 11 || freeLance == 12)  //Catch in case button mishap
    {
      freeLance = 0; //Resets loop
    }
  }
  if(path == 1)
  {
    colorCycle(freeLance);  
    freeLance--;
    if(freeLance == 0 || freeLance == -1) //Catch in case button mishap
    {
      freeLance = 12; //Resets loop
    }
  }
}
