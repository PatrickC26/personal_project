void eepromGet(){
  for(int i = 0 ; i < 10 ; i++){
    int in = EEPROM.read(i);
    charkeys[i] = char(in);
  }

  Serial.print("char key : ");
  for(int i = 0 ; i < 10 ; i++){
    Serial.print(charkeys[i]);
    Serial.print(",");
  }
  Serial.println();
}
