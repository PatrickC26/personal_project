void read(){
  
  //Waiting to read
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) ;
    byte *id = mfrc522.uid.uidByte;   // 取得卡片的UID

  u8g.firstPage();
  u8g.setFont(u8g_font_helvR14);
  u8g.setPrintPos(13, 40);
  
  
  //Print uid
  for (byte i = 0; i < mfrc522.uid.size; i++) {  // 逐一顯示UID碼
    UID[i]=mfrc522.uid.uidByte[i];
    do{
      u8g.print(UID[i],HEX);
      u8g.print(' ');
    }
    while(u8g.nextPage());
    
    //Print Error if error occur
    if (UID[i]==0){
      error();
    }
  }
  mfrc522.PICC_HaltA();  // 讓卡片進入停止模式
  write();
}
