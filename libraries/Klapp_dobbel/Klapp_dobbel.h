 #include "Arduino.h"
 
 class Klapp{
private:
uint8_t Klapp_inn;
public:
Keypad(uint8_t read_pin);
uint8_t read();
};
