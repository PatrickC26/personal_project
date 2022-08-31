unsigned long lightmillis = 0 ;

void lightTest(int lightValue){
  if (lightValue != 999){
    lightmillis = millis();
    String outS ="^";
    outS = outS + token + uid;
    Serial.print(outS + "Doing Light Test with value : ");
    Serial.println(lightValue);
  }
  
  if (millis() - lightmillis > 1500){
    for (int i = 0 ; i < 9 ; i++)
      pinMode(allkeys[i], INPUT_PULLUP);
    analogWrite(10, light);
  }
  else if (lightValue < 151){
    analogWrite(10, lightValue);
    for (int i = 0 ; i < 9 ; i++){
      pinMode(allkeys[i], OUTPUT);
      digitalWrite(allkeys[i],0);
    }
  }
}
