int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int bright = 255; //MAX light value
int delayTime; //time between light changes

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
void setColor(int red, int green, int blue) //function call to change led color
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void loop()
{
  delayTime = random(200,500);  //MAKES EACH TIME SPECIAL
  setColor(148, 0, 211);  // indigo
  delay(delayTime);
  setColor(75, bright, 130);  // dark indigo
  delay(delayTime);
  setColor(0, 0, 255);  // blue
  delay(delayTime);
  setColor(0, bright, 0);  // green
  delay(delayTime);  
  setColor(bright, bright, 0);  // yellow
  delay(delayTime);
  setColor(bright, 127, 0);  // orange
  delay(delayTime);
  setColor(bright, 0, 0);  // red
  delay(delayTime);
  setColor(bright, 127, 0);  // orange
  delay(delayTime);
  setColor(bright, bright, 0);  // yellow
  delay(delayTime);
  setColor(0, bright, 0);  // green
  delay(delayTime);
  setColor(0, 0, 255);  // blue
  delay(delayTime);
  setColor(75, bright, 130);  // dark indigo
  delay(delayTime);
}

