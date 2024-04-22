void light(int mode){
//  Serial.print("mode: ");
//  Serial.print(mode);
//  Serial.print("currentMode :");
//  Serial.print(currentMode);
  if (((mode ==  ESP_WORK) || (mode ==  FRIDGE_ERROR)) && (currentMode == ESP_ERROR)){
    mode = ESP_ERROR;
  }
  currentMode = mode;

//  Serial.print('\t');
//  Serial.print("\tAfter Edit, mode :");
//  Serial.print(mode);
//  Serial.print("currentMode :");
//  Serial.print(currentMode);
//  Serial.print('\n');
  
  switch(mode){
    case CLEAR :
      digitalWrite(RED,0);
      digitalWrite(GREEN,0);
      digitalWrite(BLUE,0);
      break;
    case ESP_WORK :
      digitalWrite(RED,0);
      digitalWrite(GREEN,0);
      digitalWrite(BLUE,1);
      break;
    case ESP_ERROR :
      digitalWrite(GREEN,0);
      digitalWrite(BLUE,0);
      digitalWrite(RED,1);
      break;
    case FRIDGE_ERROR :
      digitalWrite(RED,0);
      digitalWrite(GREEN,0);
      digitalWrite(BLUE,1);
      break;
    case FRIDGE_OK :
      if (statusB){
        Serial.println("Direct");
        delay(1000);
      }
      else{
        digitalWrite(RED,0);
        digitalWrite(GREEN,1);
        digitalWrite(BLUE,0);
        delay(2000);
        if ((fridge_time_1 != 0) || (fridge_time_2 != 0)){
          break;
        }
        light(CLEAR);
        statusB = 1;
      }
      digitalWrite(ESP_EN,0);
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
      break;
  }
}
