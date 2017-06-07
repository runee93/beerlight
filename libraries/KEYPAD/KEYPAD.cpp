#include "KEYPAD.h"

Keypad::Keypad(uint8_t read_pin){
  pot=read_pin;
  pinMode(pot,INPUT);
}

    
uint8_t Keypad::read(){
      uint8_t out=0;
      
      uint16_t verdi=analogRead(pot);
      while(verdi == 0){
          verdi=analogRead(pot);
      }
      if (verdi>875 && verdi<885){                       //1
        out=1;
        delay(100);
        }
      else if (verdi>790 && verdi<805){                  //2
        out=2;
        delay(100);
        }
      
      else if (verdi>710 && verdi<720){                  //3
        out=3;
        delay(100);
        }
      
      else if (verdi>653&& verdi<663){                  //A = 10
      out=10;
      delay(100); 
      }
      
      else if (verdi>585 && verdi<595){                  //4
      out=4;
      delay(100); 
      }
      
      else if (verdi>545 && verdi<556){                  //5
      out=5;
      delay(100);
      }
      else if (verdi>508 && verdi<518){                  //6
      out=6;
      delay(100); 
      }
      
      else if (verdi>475 && verdi<487){                  //B = 11
      out=11;
      delay(100);
      }
      
      else if (verdi>418 && verdi<430){                  //7
      out=7;
      delay(100); 
      }
      
      else if (verdi>395 && verdi<409){                  //8
      out=8;
      delay(100);
      }
      
      else if (verdi>375 && verdi<390){                  //9
      out=9;
      delay(100);
      }
      else if (verdi>360 && verdi<370){                  //C  = 12
      out=12;
      delay(100); 
      }
      
      else if (verdi>330 && verdi<341){                  //* = 14
      out=14;
      delay(100);
      }
      
      else if (verdi>316 && verdi<329){                  //0
      out=0;
      delay(100); 
      }
      
      else if (verdi>304 && verdi<315){                  //# =15
      out=15;
      delay(100);
      }
      
      else if (verdi>290 && verdi<303){                  //D = 13
      out=13;
      delay(100);
      }
      
      while(verdi!=0){
          verdi=analogRead(pot);
      }
      return out;
}
