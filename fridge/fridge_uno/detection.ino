unsigned long fridge_time_1 = 0, fridge_time_2 = 0;


void detect1(){
  if (digitalRead(2)){
    Serial.println("Fridge 1 ERROR");
    light(FRIDGE_ERROR);
    fridge_time_1 = millis();
  }
  else 
    fridge_time_1 = 0;
    
}

void detect2(){
  if (digitalRead(3)){
    Serial.println("Fridge 2 ERROR");
    light(FRIDGE_ERROR);
    fridge_time_2 = millis();
  }
  else
    fridge_time_2 = 0;

}

void detect(){
  detect1();
  detect2();
  if ((fridge_time_1 == 0) && (fridge_time_2 == 0)){
    ESP_timeout = 0;
    light(FRIDGE_OK);
  }
  else if ((fridge_time_1 > 10000) || (fridge_time_2 > 10000)){
    statusB = 0;
    ESP("FRIDGE_ERROR");
  }
  else
    statusB = 0;
}
