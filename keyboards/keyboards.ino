#include "Keyboard.h"
#include <EEPROM.h>


//      0   1    2
// A    2   3    4
// B    5   6    7
// C    8   9    15

const int allkeys[] = {2,3,4,5,6,7,8,9,15};
const String uid = "1.0.0.20220516";
char charkeys[] = {'A','B','C','D','E','F','G','H','I'};


void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  for (int i = 0 ; i < 9 ; i++){
    pinMode(allkeys[i], INPUT_PULLUP);
  }
  pinMode(10,OUTPUT);

  eepromGet();
  
  Serial.println("BEGIN");
}

void loop() {
  keyboard();
  editEvent();
}
