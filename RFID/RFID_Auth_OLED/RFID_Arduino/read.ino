int readingCount = 0 ;

String reading(byte dataBlock[]){
  // Request card to read
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_helvR14);
    u8g.setPrintPos(12, 30);
    u8g.print("Please Scan");
    u8g.setPrintPos(22, 50);
    u8g.print("Your Card");
  }
  while(u8g.nextPage());
  Serial.println("Reading");
  
  readingCount = 0 ;

  // check if has card
  while ( !(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) ){
    delay(50);
    readingCount++;
    if (readingCount > 300){
      esp.println("Q");
      return "";
    }
  }
  readingCount = 0;


  // Check for compatibility
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) 
    return reading(dataBlock);


  //variables
  byte blockAddr = 6;
  MFRC522::StatusCode status;
  byte buffer[18];
  byte size = sizeof(buffer);
  bool readingStatus = false;
  byte UID[4];
  String out = "";


  // Authenticate using key A
  Serial.println("Authenticating key A ...");
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 7, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) 
    error();

  // Authenticate using key B
  Serial.println("Authenticating key B ...");
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, 7, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) 
    error();


  // Read data from the block
  Serial.println("Reading data from block ..."); 
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) 
    return reading(dataBlock);
//  Serial.println(dump_byte_array(buffer, 16));
  out = dump_byte_array(buffer, 16);
  

  // Write data to the block
  Serial.println("Writing data into block ...");
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) 
    error();

  // Read data from the block (again, should now be what we have written)
  Serial.println("Recheck data from block ...");
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) 
    error();
//  Serial.println(dump_byte_array(buffer, 16));


  // Check the data 
  byte errcount = 0;
  for (byte i = 0; i < 16; i++) {
    if (buffer[i] == dataBlock[i])
        errcount++;
  }
  if (errcount != 16) {
    Serial.println("ERROR @ Check data");
    return "";
  }

  out += ";";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    UID[i]=mfrc522.uid.uidByte[i];
    out += String(UID[i],HEX);
    out += "-";
  }
  
  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_helvR14);
    u8g.setPrintPos(5, 40);
    u8g.print("Finish Reading");
  }
  while(u8g.nextPage());

  
  return out.substring(0, out.length() -1) + "%";
}

String dump_byte_array(byte *buffer, byte bufferSize) {
  String out = "A";
  for (byte i = 0; i < bufferSize; i++) {
    out += (buffer[i] < 0x10 ? "0" : "");
    out += String(buffer[i], HEX);
    out += ",";
  }
  return out.substring(0, out.length() -1);
}


void error(){
  u8g.firstPage();
  do{
    u8g.setFont(u8g_font_helvR14);
    u8g.setPrintPos(12, 40);
    u8g.print("ERROR occur");
  }
  while(u8g.nextPage());
  while(1);
}
