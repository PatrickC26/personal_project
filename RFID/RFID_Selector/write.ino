void write(){
  
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial());
  
  
  // Set new UID
  if (mfrc522.MIFARE_SetUid(UID, (byte)4, true) ) {

    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_helvR14);
      u8g.setPrintPos(45, 40);
      u8g.print("OK");
      u8g.setFont(u8g_font_6x10);
      u8g.setPrintPos(10, 50);
      u8g.print("Made by Sloth Maker");
    }
    while(u8g.nextPage());
    delay(2000);
  }
  else {

    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_helvR14);
      u8g.setPrintPos(35, 40);
      u8g.print("Failed");
      u8g.setFont(u8g_font_6x10);
      u8g.setPrintPos(10, 50);
      u8g.print("Made by Sloth Maker");
    }
    while(u8g.nextPage());
    delay(2000);
  }
  
  
  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();

  u8g.firstPage();
  u8g.setFont(u8g_font_helvR14);
  u8g.setPrintPos(13, 40);
  for (byte i = 0; i < 4; i++) {  // 逐一顯示UID碼
    UID[i]=mfrc522.uid.uidByte[i];
    Serial.print(UID[i],HEX);
    Serial.print('-');
    do{
      u8g.print(UID[i],HEX);
      u8g.print(' ');
    }
    while(u8g.nextPage());
  }
}
