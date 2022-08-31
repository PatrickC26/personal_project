int checkMode(){
  int getI = EEPROM.read(61);
  for (int i = 0 ; i < 9 ; i++){
    pinMode(allkeys[i], OUTPUT);
    digitalWrite(allkeys[i],1);
  }
  if (getI == 3){
    digitalWrite(allkeys[0],0);
    digitalWrite(allkeys[1],0);
    digitalWrite(allkeys[2],0);

    delay(300);
    
    digitalWrite(allkeys[0],1);
    digitalWrite(allkeys[1],1);
    digitalWrite(allkeys[2],1);

    delay(300);

    digitalWrite(allkeys[0],0);
    digitalWrite(allkeys[1],0);
    digitalWrite(allkeys[2],0);

    delay(300);
    
    digitalWrite(allkeys[0],1);
    digitalWrite(allkeys[1],1);
    digitalWrite(allkeys[2],1);

    delay(300);

    digitalWrite(allkeys[0],0);
    digitalWrite(allkeys[1],0);
    digitalWrite(allkeys[2],0);
    delay(500);
  }
  else if (getI == 2){
    digitalWrite(allkeys[0],0);
    digitalWrite(allkeys[1],0);

    delay(300);
    
    digitalWrite(allkeys[0],1);
    digitalWrite(allkeys[1],1);

    delay(300);

    digitalWrite(allkeys[0],0);
    digitalWrite(allkeys[1],0);

    delay(300);
    
    digitalWrite(allkeys[0],1);
    digitalWrite(allkeys[1],1);

    delay(300);

    digitalWrite(allkeys[0],0);
    digitalWrite(allkeys[1],0);
    delay(500);
  }
  else if (getI == 1){
    digitalWrite(allkeys[0],0);
    delay(300);
    
    digitalWrite(allkeys[0],1);
    delay(300);

    digitalWrite(allkeys[0],0);
    delay(300);
    
    digitalWrite(allkeys[0],1);
    delay(300);

    digitalWrite(allkeys[0],0);
    delay(500);
  }

  return getI;
}

int checkModeGet(){
  bool localKeysSit[] = {false,false,false,false,false,false,false,false,false};
  for (int i = 0 ; i<9 ; i++)
    localKeysSit[i] = !digitalRead(allkeys[i]);
  if (localKeysSit[0]){
    if (localKeysSit[1]){
      if (localKeysSit[2]){
        EEPROM.write(61, 3);
        return 3;
      }
      else{
        EEPROM.write(61, 2);
        return 2;
      }
    }
    else if (localKeysSit[2]){
      return EEPROM.read(61);;
    }
    else{
      EEPROM.write(61, 1);
      return 1;
    }
  }
  return EEPROM.read(61);
}
