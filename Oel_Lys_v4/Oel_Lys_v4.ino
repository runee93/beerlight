const int ShiftPWM_latchPin = 8;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>


unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 2;
unsigned int numOutputs = numRegisters * 8;
unsigned int numRGBLeds = numRegisters * 8 / 3;
unsigned int fadingMode = 0;
unsigned long startTime = 0; // start time for the chosen fading mode

uint8_t modus;
byte buttonPin = 2;
int modusFunk(void);

void oneByOne(int TID);
void inOutTwoLeds(int TID);
void inOutAll(int TID);
void alternatingColors(int TID);
void hueShiftAll(int TID);
void randomColors(int TID);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void inOutRED(int TID);
void inOutGREEN(int TID);
void inOutBLUE(int TID);
void inOutFARGE(int TID, int FARGE); //Hue
int chaseColor(int TID, int HUE, int ledibruk);
int forsink = 300;
void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  ShiftPWM.Start(pwmFrequency, maxBrightness);
  ShiftPWM.SetAll(0);
  randomSeed(analogRead(A0));

  ShiftPWM.SetRGB(0, 255, 0, 0);
  delay(forsink);
  ShiftPWM.SetRGB(1, 255, 0, 0);
  delay(forsink);
  ShiftPWM.SetRGB(2, 255, 0, 0);
  delay(forsink);
  ShiftPWM.SetRGB(3, 255, 0, 0);
  delay(forsink);
  ShiftPWM.SetRGB(4, 255, 0, 0);
  delay(forsink);
  ShiftPWM.SetRGB(0, 0, 255, 0);
  delay(forsink);
  ShiftPWM.SetRGB(1, 0, 255, 0);
  delay(forsink);
  ShiftPWM.SetRGB(2, 0, 255, 0);
  delay(forsink);
  ShiftPWM.SetRGB(3, 0, 255, 0);
  delay(forsink);
  ShiftPWM.SetRGB(4, 0, 255, 0);
  delay(forsink);
  ShiftPWM.SetRGB(0, 0, 0, 255);
  delay(forsink);
  ShiftPWM.SetRGB(1, 0, 0, 255);
  delay(forsink);
  ShiftPWM.SetRGB(2, 0, 0, 255);
  delay(forsink);
  ShiftPWM.SetRGB(3, 0, 0, 255);
  delay(forsink);
  ShiftPWM.SetRGB(4, 0, 0, 255);
  delay(forsink);
  ShiftPWM.SetRGB(0, 0, 0, 0);
  ShiftPWM.SetHSV(0,random(300,360),255,255);
  delay(forsink);
  ShiftPWM.SetRGB(1, 0, 0, 0);
  ShiftPWM.SetHSV(1,random(350),255,255);
  delay(forsink);
  ShiftPWM.SetRGB(2, 0, 0, 0);
  ShiftPWM.SetHSV(2,random(30),255,255);
  delay(forsink);
  ShiftPWM.SetRGB(3, 0, 0, 0);
  ShiftPWM.SetHSV(3,random(360),255,255);
  delay(forsink);
  ShiftPWM.SetRGB(4, 0, 0, 0);
  ShiftPWM.SetHSV(4,random(60,150),255,255);
  delay(forsink);



}
int LED;
int bruks;
void loop() {

Serial.print("Random "); Serial.println(random(360));

  if (digitalRead(buttonPin) == 1)
    modusFunk();


  if (modus == 1)
    oneByOne(1000);

  else if (modus == 2)
    inOutTwoLeds(1000);

  else if (modus == 3)
    alternatingColors(1000);

  else if (modus == 4)
    rgbLedRainbow(10000, 25);

  else if (modus == 5)
    hueShiftAll(1000);

  else if (modus == 6)
    inOutRED(1000);

  else if (modus == 7)
    inOutGREEN(1000);

  else if (modus == 8)
    inOutBLUE(1000);

  else if (modus == 9)
    randomColors(1000);

  else if (modus == 10)
    inOutFARGE(1000, 0);

  else if (modus == 11)
    inOutFARGE(1000, 30);

  else if (modus == 12)
    inOutFARGE(1000, 60);

  else if (modus == 13)
    inOutFARGE(1000, 90);

  else if (modus == 14)
    inOutFARGE(1000, 120);

  else if (modus == 15)
    inOutFARGE(1000, 150);

  else if (modus == 16)
    inOutFARGE(1000, 180);

  else if (modus == 17)
    inOutFARGE(1000, 210);

  else if (modus == 18)
    inOutFARGE(1000, 240);

  else if (modus == 19)
    inOutFARGE(1000, 270);

  else if (modus == 20)
    inOutFARGE(1000, 300);

  else if (modus == 21)
    inOutFARGE(1000, 330);

  else if (modus == 22)
    inOutFARGE(1000, 360);


  else {
    modus = 0;
    Serial.print("Modus = ");
    Serial.println(modus);
    ShiftPWM.SetAll(0);
  }

}








