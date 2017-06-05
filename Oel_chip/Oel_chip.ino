byte latchPin = 8;
byte clockPin = 13;
byte dataPin = 11;

byte knappPin=2;


volatile int modus = 0;
bool buttonState=0;
bool forste=1;
bool innei=0;

const int ShiftPWM_latchPin=8;
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad = false;
#include <ShiftPWM.h>
void oneByOne(void);
void inOutTwoLeds(void);
void inOutAll(void);
void alternatingColors(void);
void hueShiftAll(void);
void randomColors(void);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);


byte r1 = 0b00000001;
byte g1 = 0b00000010;
byte b1 = 0b00000100;
byte r2 = 0b00001000;
byte g2 = 0b00010000;
byte b2 = 0b00100000;
byte r3 = 0b01000000;
byte g3 = 0b10000000;

byte b3=0b00000001;
byte r4=0b00000010;
byte g4=0b00000100;
byte b4=0b00001000;
byte r5=0b00010000;
byte g5=0b00100000;
byte b5=0b01000000;
byte forsink=250;

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 2;
unsigned int numOutputs = numRegisters*8;
unsigned int numRGBLeds = numRegisters*8/3;
unsigned int fadingMode = 0;
unsigned long startTime = 0; // start time for the chosen fading mode


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
    ShiftPWM.SetAmountOfRegisters(numRegisters);

  ShiftPWM.SetPinGrouping(1); 

  //gjennom_alle(250);
  gjennom_alle(50);
  gjennom_alle(10);
 
  Serial.println("Klar"); 
}

void loop() {
if(digitalRead(knappPin)==1&&forste==1){
 modus++;
  Serial.print("Modus: "); 
  Serial.println(modus);
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
      all_blue();
      if(buttonState==0&&digitalRead(knappPin)==1){
        innei=0;
        all_off();
      } //end if intern
      }//end innei
     } //end if blå

if(modus==4){
        innei=1;
      while(innei==1){
      if(digitalRead(knappPin)==0&&buttonState==1){
      buttonState=0;
      delay(500);//hindre dobbelklikk
      while(digitalRead(knappPin)==0){
      Serial.println("For gjenomalle");
      gjennom_alle(500);
      Serial.println("etter gjennomalle");
      Serial.print("ButtonState "); 
      Serial.println(buttonState);
      Serial.print("digitalRead(knappPin)");
      Serial.println(digitalRead(knappPin));
      }
      }
      if(buttonState==0&&digitalRead(knappPin)==1){
        innei=0;
        Serial.println("Forfaenihelvette"); 
        all_off();
        
      } //end if intern
      }//end innei
      
     } //end if 
if(modus==5){
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
     } //end if }

if(modus==6){
  delay(1000);
ShiftPWM.Start(pwmFrequency,maxBrightness);
while(modus==6){
  ShiftPWM.SetRGB(1,255,100,255);
}
}


} //end ifs 


} //end loop()









void all_off(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin,0); //opp til g3
  shiftOut(dataPin, clockPin,0); 
  digitalWrite(latchPin, 1);  
  delay(10);

}


void all_red(){

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, r1+r2+r3); //opp til g3
  shiftOut(dataPin, clockPin, r4+r5); 
  digitalWrite(latchPin, 1);
  delay(10);
}

void all_green(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, g1+g2+g3); //opp til g3
  shiftOut(dataPin, clockPin, g4+g5); 
  digitalWrite(latchPin, 1);
  delay(10);
  

  
}
void all_blue(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, b1+b2); //opp til g3
  shiftOut(dataPin, clockPin, b3+b4+b5); 
  digitalWrite(latchPin, 1);
  delay(10);
  
  
  
}



void gjennom_alle(int forsink){
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, r1); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, r2); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);
  
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, r3); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);
  

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, r4); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, r5); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, g1); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, g2); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, g3); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, g4); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, g5); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);


  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, b1); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
    if(digitalRead(knappPin)==1){    goto bailout;     } delay(forsink);



  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, b2); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);


  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, b3); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, b4); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);


  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, b5); 
  digitalWrite(latchPin, 1);
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);
  
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); //opp til g3
  shiftOut(dataPin, clockPin, 0); 
  digitalWrite(latchPin, 1);  
      if(digitalRead(knappPin)==1){     goto bailout;      } delay(forsink);

  bailout:
  Serial.println("Nederst"); 
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

void randomColors(void){  // Update random LED to random color. Funky!
  unsigned long updateDelay = 100;
  static unsigned long previousUpdateTime;
  if(millis()-previousUpdateTime > updateDelay){
    previousUpdateTime = millis();
    ShiftPWM.SetHSV(random(numRGBLeds),random(360),255,255);
  }
}

