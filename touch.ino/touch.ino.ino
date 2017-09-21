// Paint application - Demonstate both TFT and Touch Screen
#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>
#define NUMSAMPLES 2
#define COMP       2
#define AVERAGE    1
#define RXPLATE    300
int ColorPaletteHigh = 20;
int color = WHITE;  //Paint brush color
unsigned int colors[8] = {BLACK, RED, GREEN, BLUE, CYAN, YELLOW, WHITE, GRAY1};

#if AVERAGE
#define AVERAGETIME 10
int avr_analog(int adpin)
{
    int sum = 0;
    int max = 0;
    int min = 1024;
    for(int i = 0; i<AVERAGETIME; i++)
    {
        int tmp = analogRead(adpin);
        if(tmp > max)max = tmp;
        if(tmp < min)min = tmp;
        sum += tmp;
    }
    return (sum-min-max)/(AVERAGETIME-2);

}
#endif


#define __PRESURE 5
class Point 
{
    public:
    int x, y, z;
    Point(void) { x = y = 0; }  //Default constructor and probably won't be used

    Point(int x0, int y0, int z0)  //Most used constructor
    {
      x = x0;   y = y0;   z = z0;
    }
    bool operator==(Point p1)
    {
        return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
    }
    bool operator!=(Point p1)
    {
        return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
    }

};

class TouchScreen {
    private:
    unsigned char _yp, _ym, _xm, _xp;

    public:
    TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) 
    {
        _yp = yp;
        _xm = xm;
        _ym = ym;
        _xp = xp;
    }

    bool isTouching(void)
    {
        Point p = getPoint();
        if(p.z > __PRESURE)return 1;
        else return 0;
    }
    Point getPoint(void) {
    int x, y, z = 1;
    int samples[NUMSAMPLES];

    uint8_t i, valid;

    uint8_t xp_port = digitalPinToPort(_xp);
    unsigned char yp_port = digitalPinToPort(_yp);
    unsigned char xm_port = digitalPinToPort(_xm);
    unsigned char ym_port = digitalPinToPort(_ym);

    unsigned char xp_pin = digitalPinToBitMask(_xp);
    unsigned char yp_pin = digitalPinToBitMask(_yp);
    unsigned char xm_pin = digitalPinToBitMask(_xm);
    unsigned char ym_pin = digitalPinToBitMask(_ym);
    valid = 1;
    pinMode(_yp, INPUT);
    pinMode(_ym, INPUT);

    *portOutputRegister(yp_port) &= ~yp_pin;
    *portOutputRegister(ym_port) &= ~ym_pin;

    pinMode(_xp, OUTPUT);
    pinMode(_xm, OUTPUT);

    *portOutputRegister(xp_port) |= xp_pin;
    *portOutputRegister(xm_port) &= ~xm_pin;

    for (i=0; i<NUMSAMPLES; i++)
    {
#if AVERAGE
        samples[i] = avr_analog(_yp);
#else
        samples[i] = analogRead(_yp);
#endif
    }

#if !COMP
    if (samples[0] != samples[1]) { valid = 0; }
#else
    int icomp = samples[0]>samples[1]?samples[0]-samples[1]:samples[1] - samples[0];
    if(icomp > COMP)valid = 0;
#endif

    x = (samples[0] + samples[1]);

    pinMode(_xp, INPUT);
    pinMode(_xm, INPUT);
    *portOutputRegister(xp_port) &= ~xp_pin;

    pinMode(_yp, OUTPUT);
    *portOutputRegister(yp_port) |= yp_pin;
    pinMode(_ym, OUTPUT);

    for (i=0; i<NUMSAMPLES; i++) {
#if AVERAGE
        samples[i] = avr_analog(_xm);
#else
        samples[i] = analogRead(_xm);
#endif
    }

#if !COMP
    if (samples[0] != samples[1]) { valid = 0; }
#else
    icomp = samples[0]>samples[1]?samples[0]-samples[1]:samples[1] - samples[0];
    if(icomp>COMP)valid = 0;
#endif
    y = (samples[0]+samples[0]);

    pinMode(_xp, OUTPUT);
    *portOutputRegister(xp_port) &= ~xp_pin;            // Set X+ to ground
    *portOutputRegister(ym_port) |=  ym_pin;            // Set Y- to VCC
    *portOutputRegister(yp_port) &= ~yp_pin;            // Hi-Z X- and Y+
    pinMode(_yp, INPUT);

    int z1          = analogRead(_xm);
    int z2          = analogRead(_yp);
    float rtouch    = 0;

    rtouch  = z2;
    rtouch /= z1;
    rtouch -= 1;
    rtouch *= (2046-x)/2;
    rtouch *= RXPLATE;
    rtouch /= 1024;
    z = rtouch;
    if (! valid) {
        z = 0;
    }

    return Point(x, y, z);
}


};
/****************************************************************************************************/
TouchScreen ts = TouchScreen(XP, YP, XM, YM); //init TouchScreen port pins

void setup()
{
    Tft.TFTinit();  //init TFT library
    Serial.begin(115200);
    //Draw the pallet
    for(int i = 0; i<8; i++)
    {
        Tft.fillRectangle(i*30, 0, 30, ColorPaletteHigh, colors[i]);
    }
}
int MYNUMBER=2;
void loop()
{
    // a point object holds x y and z coordinates.
    Point p = ts.getPoint();

    //map the ADC value read to into pixel co-ordinates

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    if (p.z > __PRESURE) {
        // Detect  paint brush color change
        if(p.y < ColorPaletteHigh+2)
        {
            color = colors[p.x/30];
        }
        else
        {
          if(p.y > 280 && p.x>90)
          {
            MYNUMBER++;
            String buff = String(MYNUMBER);
            
            char* taco = (char*)buff.c_str();
            Tft.fillRectangle(0,280,300,40,BLACK);
            Tft.drawString(taco,50,280,4,WHITE);
            delay(250);
            
          }
          if(p.y > 280 && p.x<20)
          {
            MYNUMBER--;
            String buff = String(MYNUMBER);
            char* taco = (char*)buff.c_str();
            Tft.fillRectangle(0,280,300,40,BLACK);
            Tft.drawString(taco,50,280,3,WHITE);
            delay(250);
          }
            Tft.fillCircle(p.x,p.y,MYNUMBER,color);
        }
    }
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
