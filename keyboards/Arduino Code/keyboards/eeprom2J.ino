void eeprom2J(){
  int AC1[9], AC2[9], AC3[9], BC1[9], BC2[9], BC3[9];
  int ModesAvailable[3], light;
  
  for(int i = 0 ; i < 9 ; i++)
    AC1[i] = EEPROM.read(i);
//
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



  Serial.print("A:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(AC1[i]);
    Serial.print(";");
    Serial.print(BC1[i]);
    Serial.print(",");
  }
  Serial.print("%\nB:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(AC2[i]);
    Serial.print(";");
    Serial.print(BC2[i]);
    Serial.print(",");
  }
  Serial.print("%\nC:");
  for(int i = 0 ; i < 9 ; i++){
    Serial.print(AC3[i]);
    Serial.print(";");
    Serial.print(BC3[i]);
    Serial.print(",");
  }
  Serial.print("%\nD:");
  Serial.print(light);
  Serial.print(",");
  for(int i = 0 ; i < 3 ; i++){
    Serial.print(ModesAvailable[i]);
    Serial.print(",");
  }
  Serial.println("%");


}
