#include "Keyboard.h"
#include <EEPROM.h>

#define token "keys3x3sloth"
#define uid "1.0.4.20220828"

//      0   1    2
// A    2   3    4
// B    5   6    7
// C    8   9    15

//const int allkeys[] = {2,3,4,5,6,7,8,9,10};
const int allkeys[] = {2,3,4,5,6,7,8,9,15};

int funckeys[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char charkeys[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int light = 0;


// ||
// ||==   => this side negative on leds
// ||


void setup() {
  pinMode(10,OUTPUT);
  analogWrite(10, 10); // up to 150

  Serial.begin(9600);
  Serial.setTimeout(100);
  Keyboard.begin();

  for (int i = 0 ; i < 9 ; i++){
    pinMode(allkeys[i], INPUT_PULLUP);
  }

  checkModeGet();
  
  
  for (int i = 0 ; i < 9 ; i++){
    pinMode(allkeys[i], OUTPUT);
    digitalWrite(allkeys[i],0);
    delay(100);
  }


  eepromGet();
  checkMode();
  
  
  for (int i = 0 ; i < 9 ; i++){
    pinMode(allkeys[i], INPUT_PULLUP);
  }
  
  Serial.println("BEGIN");
}

void loop() {
  keyboard();
  keysOperate();
  editEvent();
  lightTest(999);
}
