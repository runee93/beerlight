

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

int modusFunk(void);

void inOutTwoLeds(unsigned int TID);
void inOutAll(unsigned int TID);
void alternatingColors(unsigned int TID);
void hueShiftAll(unsigned int TID);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void inOutRED(unsigned int TID);
void inOutGREEN(unsigned int TID);
void inOutBLUE(unsigned int TID);
void inOutFARGE(unsigned int TID, int FARGE); //Hue
int chaseColor(unsigned int TID, int HUE, int ledibruk);
void oppstartfunk();
int forsink = 150;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  ShiftPWM.Start(pwmFrequency, maxBrightness);
  ShiftPWM.SetAll(0);
  randomSeed(analogRead(A0));
  delay(1000);
  oppstartfunk();
  delay(1000); //1500 gir smud overgang til rainbow 10000, 50
  Serial.println("Modus 1");

}
                                                                                           

void loop() {
  if (digitalRead(buttonPin) == 1)
    modusFunk();

      
  if (modus == 0){
  ShiftPWM.SetAll(0);
  while(digitalRead(buttonPin)); delay(1);
  }

  else if (modus == 1){
    rgbLedRainbow(100000, 5);
  }
  else if (modus == 2){
    rgbLedRainbow(100000, 50); 
  }
  else if (modus == 3)
    rgbLedRainbow(100000, 50);

  else if (modus == 4)
    rgbLedRainbow(1000, 50);

  else if (modus == 5)
    hueShiftAll(50000);
        
  else if (modus == 6)
    hueShiftAll(1000000);
    
  else if (modus == 7)
    alternatingColors(1000);
  
  
  else if (modus == 8)
    alternatingColors(10000);
  
  else if (modus == 9)
  inOutRED(10000);
  
  else if (modus == 10)
  inOutGREEN(10000);

  else if (modus == 11)
  inOutBLUE(10000);
  
  else if (modus == 12)
  inOutFARGE(10000, 32);




  else {
    modus = 0;
    Serial.print("Modus = ");
    Serial.println(modus);
    ShiftPWM.SetAll(0);
  }

}








