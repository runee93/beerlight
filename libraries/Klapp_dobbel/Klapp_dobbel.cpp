#include "Klapp_dobbel.h"

Klapp_dobbel::Klapp_dobbel(uint8_t read_pin){
  klappInn=read_pin;
  pinMode(klapp,INPUT);
}

uint8_t Klapp_dobbel::read(){
	uint8_t out=0;
	klapp=digitalRead(klappInn);
  if(klapp==1&&state==0){
    count=1;    
    Serial.println("en pa");
    delay(100);
    start=millis()/1000;
    while(millis()/1000<1+start){
      klapp=0;
      klapp=digitalRead(klappInn);
      if(klapp==1){
      count=2;
      Serial.println("to pa");
      out=1;
      state=1;
      klapp=0;
      delay(250);
      break;
      }
      }
      
      if(count==1){
        count=0;
         Serial.println("time out paa");
         Serial.print("millis() :");
         Serial.println(millis()/1000);
         Serial.print("start+1: " );
         Serial.println(start+1);
         delay(100);
}      
}
  if(klapp==1&&state==1){
    count=1;    
    Serial.println("en av");
    delay(100);
    start=millis()/1000;
    while(millis()/1000<1+start){
      klapp=0;
      klapp=digitalRead(klappInn);
      if(klapp==1){
      count=2;
      Serial.println("to av");
      out=0;
      state=0;
      klapp=0;
      delay(250);
      break;
      }
      }
      
      if(count==1){
        count=0;
         Serial.println("time out av");
         Serial.println(millis());
         delay(100);
  } 
 }
	
	
}