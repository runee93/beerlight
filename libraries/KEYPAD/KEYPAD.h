 #include "Arduino.h"

class Keypad{
private:
uint8_t pot;
public:
Keypad(uint8_t read_pin);
uint8_t read();
};
