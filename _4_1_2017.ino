int led = 12; //Assigns active pin (avoiding pin 13 for debug)
int freeLance;
void setup() 
{                
  pinMode(led, OUTPUT); // initialize the digital pin as an output.    
}

void fastBlip()
{
  digitalWrite(led,HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100); // wait for 1/10 second
  digitalWrite(led,LOW); // turn the LED off by making the voltage LOW
  delay(100); // wait for 1/10 second
}
void slowBlip()
{
  digitalWrite(led,HIGH); // turn the LED on (HIGH is the voltage level)
  delay(400); // wait for a second
  digitalWrite(led,LOW); // turn the LED off by making the voltage LOW
  delay(400); // wait for a second
}

void loop() 
{
    freeLance = random(0,2);
    if(freeLance == 1)
    {
      fastBlip();            
    }
    else
    {
      slowBlip();
    }
}

