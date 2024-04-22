void loop(){
  // Serial on Uno
  if(Uno.available()){
    char inC = Uno.read();
    Serial.println(inC);
    
    if (inC == 'E'){
      LINE.notify("請將冰箱門關好！");
      Serial.print("C%");
      Uno.print("C%");
    }
    else if (inC == 'T'){
      LINE.notify("開機訊息測試！");
      Serial.print("C%");
      Uno.print("C%");
    }

  }

  // Serial on PC
  if(Serial.available()){
    char inC = Serial.read();
    Serial.println(inC);
    
    if (inC == 'E'){
      LINE.notify("請將冰箱門關好！");
      Serial.print("C%");
      Uno.print("C%");
    }
    else if (inC == 'T'){
      LINE.notify("開機訊息測試！");
      Serial.print("C%");
      Uno.print("C%");
    }

  }
}
