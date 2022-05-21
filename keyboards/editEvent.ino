void editEvent(){
  while(Serial.available()){
    char inC = Serial.read();
    if (inC == '$')
      Serial.println(uid);
    else if (inC == '&'){
      if (Serial.read() == '#'){
        for(int i = 0 ; i < 10 ; i++){
          EEPROM.write(i, Serial.read()); 
        }
      }
      eepromGet();
    }
  }
}
