void setup() {
  Serial.begin(9600);
  Serial.println("BEGIN");
  
  esp.begin(9600);
  pinMode(ESP_EN,OUTPUT);
  digitalWrite(ESP_EN,0);
  ESP("TEST");

  pinMode(ThermistorPin1, INPUT_PULLUP);
  pinMode(ThermistorPin2, INPUT_PULLUP);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  attachInterrupt(0, detect_Intr, RISING);
  attachInterrupt(1, detect_Intr, RISING);
}


void detect_Intr(){
  statusB = 0;
  detect1();
  detect2();
}

void loop() {
  if (!statusB){
    SerialEvent();
    ESPLoop();
  }

  if ((millis()-lastDetectMillis > 60*1000) || (lastDetectMillis == 0)){
    temperature();
    lastDetectMillis = millis();
  }
  
  detect();

  delay(500);
}
