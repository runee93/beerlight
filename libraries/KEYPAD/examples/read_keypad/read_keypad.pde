#include <KEYPAD.h>


void setup(){
  Serial.begin(9600);
}
Keypad keypad(A0);
void loop(){
 
  uint8_t temp =28;
  while(temp==28){
    temp=keypad.read();
  }
  Serial.print("Keypad read:\t");
  Serial.println(temp, HEX);
}
