void ESP(String S){
  if (S == "FRIDGE_ERROR"){
    ESP_Value = "E%";
  }
  else if(S == "TEST"){
    ESP_Value = "T%";
  }
  light(ESP_WORK);
  if (ESP_timeout == 0){
    ESP_timeout = millis();
  }
  digitalWrite(ESP_EN,1);
}

void ESPLoop(){
  if (ESP_Value != ""){
    if (millis() - preMillis > 100000){
      esp.print(ESP_Value);
      Serial.print(ESP_Value);
      delay(50);
      preMillis = millis();
    }
  }

  if ((millis() - ESP_timeout > 10000) && (ESP_timeout != 0)){
    light(ESP_ERROR);
    Serial.println("ESP_ERROR");
  }
}


void SerialEvent(){
  if (Serial.available()){
    char inC = Serial.read();
    if (inC == 'C'){
      Serial.println("Clear");
      ESP_timeout = 0;
      ESP_Value = "";
      light(CLEAR);
    }
  }

  if (esp.available()){
    char inC = esp.read();
    if (inC == 'C'){
      Serial.println("Clear");
      ESP_timeout = 0;
      ESP_Value = "";
      light(CLEAR);
    }
  }
}
