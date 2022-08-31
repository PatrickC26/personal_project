int eepromGet(){
  int AC1[9], AC2[9], AC3[9];
  int BC1[9], BC2[9], BC3[9];
  int currentMode = 0, ModesAvailable[3] ;
  
  for(int i = 0 ; i < 9 ; i++)
    AC1[i] = EEPROM.read(i);

  for(int i = 0 ; i < 9 ; i++)
    AC2[i] = EEPROM.read(i+9);

  for(int i = 0 ; i < 9 ; i++)
    AC3[i] = EEPROM.read(i+18);

  for(int i = 0 ; i < 9 ; i++)
    BC1[i] = EEPROM.read(i+30);

  for(int i = 0 ; i < 9 ; i++)
    BC2[i] = EEPROM.read(i+39);

  for(int i = 0 ; i < 9 ; i++)
    BC3[i] = EEPROM.read(i+48);

  light = EEPROM.read(57);
  
  
  for(int i = 0 ; i < 3 ; i++)
    ModesAvailable[i] = EEPROM.read(i+58);

  currentMode = EEPROM.read(61);



  Serial.print("A1:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(AC1[i]);
    Serial.print(",");
  }
  Serial.print("%\nA2:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(AC2[i]);
    Serial.print(",");
  }
  Serial.print("%\nA3:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(AC3[i]);
    Serial.print(",");
  }
  Serial.print("%\nB1:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(BC1[i]);
    Serial.print(",");
  }
  Serial.print("%\nB2:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(BC2[i]);
    Serial.print(",");
  }
  Serial.print("%\nB3:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(BC3[i]);
    Serial.print(",");
  }


  Serial.print("\nlight : ");
  Serial.print(light);
  
  Serial.print("%\nCM:");
  Serial.print(currentMode);
  
  Serial.print("%\nMA:");
  for(int i = 0 ; i < 3 ; i++){
    Serial.print(ModesAvailable[i]);
    Serial.print(",");
  }
  Serial.println();

  // Mode decision
  if (ModesAvailable[2] == 0 && currentMode == 3)
    currentMode = 2;
  if (ModesAvailable[1] == 0 && currentMode == 2)
    currentMode = 1;
  if (ModesAvailable[0] == 0 && currentMode == 1)
    currentMode = 0;
  if (currentMode != 1 && currentMode != 2 && currentMode != 3)
    currentMode = 1;

  EEPROM.write(61, currentMode);


  // Keyboard keys
  if (currentMode == 1){
    for(int i = 0 ; i<9 ; i++){
      charkeys[i] = BC1[i];
      funckeys[i] = AC1[i];
    }
  }
  if (currentMode == 2){
    for(int i = 0 ; i<9 ; i++){
      charkeys[i] = BC2[i];
      funckeys[i] = AC2[i];
    }
  }
  if (currentMode == 3){
    for(int i = 0 ; i<9 ; i++){
      charkeys[i] = BC3[i];
      funckeys[i] = AC3[i];
    }
  }
  

  // Change light status 
  if (light > 150)
    light = 150;
  analogWrite(10, light); // up to 150
}
