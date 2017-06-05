byte b3 = 0b00000001;
byte r4 = 0b00000010;
byte g4 = 0b00000100;
byte b4 = 0b00001000;
byte r5 = 0b00010000;
byte g5 = 0b00100000;
byte b5 = 0b01000000;
byte g3 = 0b10000000;

byte r1=0b00000001;
byte g1=0b00000010;
byte b1=0b00000100;
byte r2=0b00001000;
byte g2=0b00010000;
byte b2=0b00100000;
byte r3=0b01000000;
byte forsink=250;


const int ShiftPWM_latchPin=8;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>


unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 2;
unsigned int numOutputs = numRegisters*8;
unsigned int numRGBLeds = numRegisters*8/3;
unsigned int fadingMode = 0;
unsigned long startTime = 0; // start time for the chosen fading mode

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;


uint8_t knappPin=2;
volatile int modus = 0;
bool buttonState=0;
bool forste=1;
bool innei=0;

void oneByOne(void);
void inOutTwoLeds(int TID);
void inOutAll(int TID);
void alternatingColors(int TID);
void hueShiftAll(int TID);
void randomColors(int TID);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void inOutRED(int TID);
void inOutGREEN(int TID);
void inOutBLUE(int TID);

void setup() {

  pinMode(latchPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(dataPin, OUTPUT);

  ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  pinMode(knappPin, INPUT);


  gjennom_alle(250);
  gjennom_alle(50);

} //End setup()


void loop() {
if(digitalRead(knappPin)==1&&forste==1){
 modus=modus+1;
   delay(10);
 buttonState=1;
 if(modus==1){ //rød
      innei=1;
      while(innei==1){
      if(digitalRead(knappPin)==0&&buttonState==1){
      buttonState=0;}
      all_red();

      if(buttonState==0&&digitalRead(knappPin)==1){
        innei=0;
        all_off();
      } //end if intern
      }//end innei
     } //end if rød

if(modus==2){ //grønn
      innei=1;
      while(innei==1){
      if(digitalRead(knappPin)==0&&buttonState==1){
      buttonState=0;}
      all_green();
      if(buttonState==0&&digitalRead(knappPin)==1){
        innei=0;
        all_off();
      } //end if intern
      }//end innei
     } //end if grønn
     
if(modus==3){ //blå
      innei=1;
      while(innei==1){
      if(digitalRead(knappPin)==0&&buttonState==1){
      buttonState=0;}
      ShiftPWM.Start(pwmFrequency,maxBrightness);
      while(true){
        rgbLedRainbow(10000,10);
     }
      }

}
}//end main if
    
  

  delay(100);





}//end loop


void interruptFunk(){
modus=modus+1;
  
}


void all_off(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //opp til g3
  shiftOut(dataPin, clockPin,0); 
  digitalWrite(latchPin, 1);  
  delay(10);

}


void all_red(){

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,r4+r5); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,r1+r2+r3); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2) 
  digitalWrite(latchPin, 1);
  delay(10);

}

void all_green(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,g4+g5); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,g1+g2+g3); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(10);
  

  
}
void all_blue(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,b3+b4+b5); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,b1+b2); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(10);
  
  
  
}



void gjennom_alle(int forsink){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,r1); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,r2); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,r3); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,r4); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,r5); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,g1); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,g2); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,g3); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,g4); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,g5); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,b1); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,b2); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,b3); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,b4); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,b5); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
  delay(forsink);
  
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //Fra b3 til b5 (r4 r5 g4 g5 b3 b4 b5)
  shiftOut(dataPin, clockPin,0); //Fra r1 til b2 (r1 r2 r3 g1 g2 g3 b1 b2)
  digitalWrite(latchPin, 1);
}







void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;


  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOutï¿½
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

void oneByOne(void){ // Fade in and fade out all outputs one at a time
  unsigned char brightness;
  unsigned long fadeTime = 500;
  unsigned long loopTime = numOutputs*fadeTime*2;
  unsigned long time = millis()-startTime;
  unsigned long timer = time%loopTime;
  unsigned long currentStep = timer%(fadeTime*2);

  int activeLED = timer/(fadeTime*2);

  if(currentStep <= fadeTime ){
    brightness = currentStep*maxBrightness/fadeTime; ///fading in
  }
  else{
    brightness = maxBrightness-(currentStep-fadeTime)*maxBrightness/fadeTime; ///fading out;
  }
  ShiftPWM.SetAll(0);
  ShiftPWM.SetOne(activeLED, brightness);
}

void inOutTwoLeds(int TID){ // Fade in and out 2 outputs at a time
  unsigned long fadeTime = TID;
  unsigned long loopTime = numOutputs*fadeTime;
  unsigned long time = millis()-startTime;
  unsigned long timer = time%loopTime;
  unsigned long currentStep = timer%fadeTime;

  int activeLED = timer/fadeTime;
  unsigned char brightness = currentStep*maxBrightness/fadeTime;

  ShiftPWM.SetAll(0);
  ShiftPWM.SetOne((activeLED+1)%numOutputs,brightness);
  ShiftPWM.SetOne(activeLED,maxBrightness-brightness);
}

void inOutAll(int TID){  // Fade in all outputs
  unsigned char brightness;
  unsigned long fadeTime = TID;
  unsigned long time = millis()-startTime;
  unsigned long currentStep = time%(fadeTime*2);

  if(currentStep <= fadeTime ){
    brightness = currentStep*maxBrightness/fadeTime; ///fading in
  }
  else{
    brightness = maxBrightness-(currentStep-fadeTime)*maxBrightness/fadeTime; ///fading out;
  }
  ShiftPWM.SetAll(brightness);
}

void inOutRED(int TID){  // Fade in all red
  unsigned char brightness;
  unsigned long fadeTime = TID;
  unsigned long time = millis()-startTime;
  unsigned long currentStep = time%(fadeTime*2);

  if(currentStep <= fadeTime ){
    brightness = currentStep*maxBrightness/fadeTime; ///fading in
  }
  else{
    brightness = maxBrightness-(currentStep-fadeTime)*maxBrightness/fadeTime; ///fading out;
  }
  ShiftPWM.SetRGB(0,brightness,0,0);
  ShiftPWM.SetRGB(1,brightness,0,0);
  ShiftPWM.SetRGB(2,brightness,0,0);
  ShiftPWM.SetRGB(3,brightness,0,0);
  ShiftPWM.SetRGB(4,brightness,0,0);
}

void alternatingColors(int TID){ // Alternate LED's in 6 different colors
  unsigned long holdTime = TID;
  unsigned long time = millis()-startTime;
  unsigned long shift = (time/holdTime)%6;
  for(unsigned int led=0; led<numRGBLeds; led++){
    switch((led+shift)%6){
    case 0:
      ShiftPWM.SetRGB(led,255,0,0);    // red
      break;
    case 1:
      ShiftPWM.SetRGB(led,0,255,0);    // green
      break;
    case 2:
      ShiftPWM.SetRGB(led,0,0,255);    // blue
      break;
    case 3:
      ShiftPWM.SetRGB(led,255,128,0);  // orange
      break;
    case 4:
      ShiftPWM.SetRGB(led,0,255,255);  // turqoise
      break;
    case 5:
      ShiftPWM.SetRGB(led,255,0,255);  // purple
      break;
    }
  }
}

void hueShiftAll(int TID){  // Hue shift all LED's
  unsigned long cycleTime = TID;
  unsigned long time = millis()-startTime;
  unsigned long hue = (360*time/cycleTime)%360;
  ShiftPWM.SetAllHSV(hue, 255, 255); 
}

void randomColors(int TID){  // Update random LED to random color. Funky!
  unsigned long updateDelay = TID;
  static unsigned long previousUpdateTime;
  if(millis()-previousUpdateTime > updateDelay){
    previousUpdateTime = millis();
    ShiftPWM.SetHSV(random(numRGBLeds),random(360),255,255);
  }
}


void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth){
  // Displays a rainbow spread over a few LED's (numRGBLeds), which shifts in hue. 
  // The rainbow can be wider then the real number of LED's.
  unsigned long time = millis()-startTime;
  unsigned long colorShift = (360*time/cycleTime)%360; // this color shift is like the hue slider in Photoshop.

  for(unsigned int led=0;led<numRGBLeds;led++){ // loop over all LED's
    int hue = ((led)*360/(rainbowWidth-1)+colorShift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
    ShiftPWM.SetHSV(led, hue, 255, 255); // write the HSV values, with saturation and value at maximum
  }
}
