void setup() {
  // start page
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_helvR14);
    u8g.setPrintPos(9, 30);
    u8g.print("Authenticator");
    u8g.setFont(u8g_font_6x10);
    u8g.setPrintPos(10, 50);
    u8g.print("Made by Sloth Maker");
  }
  while(u8g.nextPage());
  
  //begin Serials
  Serial.begin(9600);
  Serial.setTimeout(100);
  esp.begin(9600);
  esp.setTimeout(100);
  
  //begin SPI
  SPI.begin();
  
  //begin mfrc
  mfrc522.PCD_Init();

  //begin key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  delay(2000);
  esp.println("Q");
  Serial.println("READY");
}


void loop(){
  serial();

  // if past 4 sec seemed it disconnected
  if ((millis() - lmillis_connection > 4000) ){
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_helvR14);
      u8g.setPrintPos(0, 30);
      u8g.print("Please connect");
      u8g.setPrintPos(25, 50);
      u8g.print("to  Wi-Fi");
    }
    while(u8g.nextPage());
    lmillis_connection = millis();
  }
  
}
