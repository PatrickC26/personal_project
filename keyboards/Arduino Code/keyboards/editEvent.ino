void editEvent(){
  while(Serial.available()){
    char inC = Serial.read();
    if (inC == '$'){
      String out = "^";
      out = out + token + uid;
      Serial.println(out);
    }
    else if (inC == '#'){
      delay(10);
//      inC = Serial.read();
//      Serial.println(inC);
      if (Serial.read() == '&'){
        delay(10);
        for(int i = 0 ; i < 61 ; i++){
          int a = Serial.parseInt();
          EEPROM.write(i, a);
          Serial.println(a);
        }
      }
      eepromGet();
    }
    else if (inC == '@'){
      eeprom2J();
    }
    else if (inC == 'L'){
      delay(5);
      lightTest(Serial.parseInt());
    }
  }
}
