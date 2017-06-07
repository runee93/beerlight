/*
void inOutTwoLeds(unsigned int TID);
void inOutAll(unsigned int TID);
void alternatingColors(unsigned int TID);
void hueShiftAll(unsigned int TID);
void randomColors(unsigned int TID);
void rgbLedRainbow(unsigned long cycleTime, int rainbowWidth);
void inOutRED(unsigned int TID);
void inOutGREEN(unsigned int TID);
void inOutBLUE(unsigned int TID);
*/



void inOutTwoLeds(unsigned int TID){ // Fade in and out 2 outputs at a time
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

void inOutAll(unsigned int TID){  // Fade in all outputs
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

void inOutRED(unsigned int TID){  // Fade in all red
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

void inOutGREEN(unsigned int TID){  // Fade in all Gron
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
  ShiftPWM.SetRGB(0,0,brightness,0);
  ShiftPWM.SetRGB(1,0,brightness,0);
  ShiftPWM.SetRGB(2,0,brightness,0);
  ShiftPWM.SetRGB(3,0,brightness,0);
  ShiftPWM.SetRGB(4,0,brightness,0);
}

void inOutBLUE(unsigned int TID){  // Fade in all bla
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
  ShiftPWM.SetRGB(0,0,0,brightness);
  ShiftPWM.SetRGB(1,0,0,brightness);
  ShiftPWM.SetRGB(2,0,0,brightness);
  ShiftPWM.SetRGB(3,0,0,brightness);
  ShiftPWM.SetRGB(4,0,0,brightness);
}

void inOutFARGE(unsigned int TID,int FARGE){  // Fade in all FARGE
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
  ShiftPWM.SetHSV(0,FARGE,255,brightness);
  ShiftPWM.SetHSV(1,FARGE,255,brightness);
  ShiftPWM.SetHSV(2,FARGE,255,brightness);
  ShiftPWM.SetHSV(3,FARGE,255,brightness);
  ShiftPWM.SetHSV(4,FARGE,255,brightness);
}

void alternatingColors(unsigned int TID){ // Alternate LED's in 6 different colors
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

void hueShiftAll(long TID){  // Hue shift all LED's
  unsigned long cycleTime = TID;
  unsigned long time = millis()-startTime;
  unsigned long hue = (360*time/cycleTime)%360;
  ShiftPWM.SetAllHSV(hue, 255, 255); 
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

int chaseColor(unsigned int TID, int HUE, int ledibruk){ //HUE 1000 ==random farger
 int numRGBLeds=5;
  int topp;
  unsigned char brightness;
  unsigned long fadeTime = TID;
  unsigned long loopTime = numOutputs*fadeTime*2;
  unsigned long time = millis()-startTime;
  unsigned long timer = time%loopTime;
  unsigned long currentStep = timer%(fadeTime*2);

  ShiftPWM.SetHSV(ledibruk,315,255,255);
  
for(unsigned int led=0;led<numRGBLeds;led++){
  ShiftPWM.SetHSV(led,105,255,255);
  delay(1000);

}
  
}


void oppstartfunk(){

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
  
/*  ShiftPWM.SetRGB(0, 0, 0, 0);
  ShiftPWM.SetHSV(0,192,255,255);
  delay(forsink);
  ShiftPWM.SetRGB(1, 0, 0, 0);
  ShiftPWM.SetHSV(1,32,255,255);
  delay(forsink);
  ShiftPWM.SetRGB(2, 0, 0, 0);
  ShiftPWM.SetHSV(2,224,255,255);
  delay(forsink);
  ShiftPWM.SetRGB(3, 0, 0, 0);
  ShiftPWM.SetHSV(3,64,255,255);
  delay(forsink);
  ShiftPWM.SetRGB(4, 0, 0, 0);
  ShiftPWM.SetHSV(4,128,255,255);
  delay(forsink);
*/
}
