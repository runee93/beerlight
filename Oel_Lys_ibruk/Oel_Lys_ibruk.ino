

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

uint8_t modus=1;
byte buttonPin = 2;
byte klappInn= 12;

int modusFunk(void);
void klappFunk(void);

void inOutTwoLeds(unsigned int TID);
void inOutAll(unsigned int TID);
void alternatingColors(unsigned int TID);
void hueShiftAll(unsigned int TID);
void randomColors(unsigned int TID);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void inOutRED(unsigned int TID);
void inOutGREEN(unsigned int TID);
void inOutBLUE(unsigned int TID);
void inOutFARGE(unsigned int TID, int FARGE); //Hue
int chaseColor(unsigned int TID, int HUE, int ledibruk);
void oppstartfunk();
int forsink = 300;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(klappInn, INPUT);
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  ShiftPWM.Start(pwmFrequency, maxBrightness);
  ShiftPWM.SetAll(0);
  randomSeed(analogRead(A0));
  delay(1000);
  oppstartfunk();
  delay(1000); //1500 gir smud overgang til rainbow 10000, 50

}
                                                                                           

void loop() {
//  if (digitalRead(buttonPin) == 1)
//    modusFunk();
  if (digitalRead(klappInn) == 1)
    klappFunk();
    
Serial.print("Modus: ");
Serial.println(modus);  
  if (modus == 0){
  ShiftPWM.SetAll(0);
  while(digitalRead(buttonPin)); delay(1);
  }

  else if (modus == 1){
    rgbLedRainbow(10000, 50); //10000,50 gir smud overgang med oppstartsfunk

  }
  else if (modus == 2){
    rgbLedRainbow(100000, 50);
   // delay(10); //klapp funker dårlig med denne, men tror lyset blir penere?
  }
  else if (modus == 3)
    rgbLedRainbow(100000, 5);

  else if (modus == 4)
    hueShiftAll(50000);

  else if (modus == 5)
    alternatingColors(1000);
  
  
  else if (modus == 6)
    alternatingColors(500);

  else if (modus == 7)
    alternatingColors(250);

  else if (modus == 8)
    randomColors(1000);
  
  else if (modus == 9)
    randomColors(500);

  else if (modus == 10)
  randomColors(250);
  
  else if (modus == 11)
  inOutTwoLeds(1000);

  else if (modus == 12)
  inOutRED(10000);
  
  else if (modus == 13)
  inOutGREEN(10000);

  else if (modus == 14)
  inOutBLUE(10000);
  
  else if (modus == 15)
  inOutFARGE(10000, 32);

  else if (modus == 16)
  inOutFARGE(10000, 224);

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








