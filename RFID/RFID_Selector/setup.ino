void setup(){
  int timeI = 5, modeI = 0;
  unsigned long lmillis = 0;
  
  pinMode(4,INPUT_PULLUP);
  
  //begin Serials
  Serial.begin(9600);
  Serial.setTimeout(100);
  esp.begin(9600);
  esp.setTimeout(100);
  
  Serial.println("START");

  //begin SPI
  SPI.begin();
  
  //begin mfrc
  mfrc522.PCD_Init();

  //begin key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  while (true){
    if (!digitalRead(4)){
      modeI++;
      modeI %= 3;
      delay(100);
      timeI = 5;
      lmillis = millis();
    }

    if (millis() - lmillis > 1000){
      timeI--;
      lmillis = millis();
    }
    
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_helvB08);
      u8g.setPrintPos(4, 13 + modeI*15);
      u8g.print("V");
      
      u8g.setFont(u8g_font_helvB10);
      u8g.setPrintPos(15, 15);
      u8g.print("Authenticator");
      u8g.setFont(u8g_font_helvB10);
      u8g.setPrintPos(15, 30);
      u8g.print("Duplicator");
      u8g.setFont(u8g_font_helvB10);
      u8g.setPrintPos(15, 45);
      u8g.print("Uart Duplicator");
      
      u8g.setFont(u8g_font_6x10);
      u8g.setPrintPos(0, 60);
      u8g.print("Made by Sloth Maker");

      u8g.setFont(u8g_font_6x10);
      u8g.setPrintPos(120, 60);
      u8g.print(timeI);
      Serial.println("C");
    }
    while(u8g.nextPage());

    if (timeI == 0)
      break;
  }

  Serial.print("Mode Choosen : ");
  Serial.println(modeI);

  if (modeI == 0){ // Authenticator
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
  }
  else if (modeI == 1){  // Duplicator
    // start page
    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_helvR14);
      u8g.setPrintPos(9, 30);
      u8g.print("Duplicator");
      u8g.setFont(u8g_font_6x10);
      u8g.setPrintPos(10, 50);
      u8g.print("Made by Sloth Maker");
    }
    while(u8g.nextPage());

    delay(1000);

    u8g.firstPage();
    do{
      u8g.setFont(u8g_font_helvR14);
      u8g.setPrintPos(25, 40);
      u8g.print("READY");
    }
    while(u8g.nextPage());
    
    read();
  }
  else if (modeI == 2){ // UART Duplicator
    u8g.firstPage();
    u8g.setFont(u8g_font_helvR14);
    do {
      u8g.setPrintPos(15, 40); // (x,y)
      u8g.println("UART mode");
    }
    while(u8g.nextPage());
    
    Serial.println("Please Enter a UID (4 UID only & Form should be correct) Ex:AA;3B;6C;FF;");
    int UIDno = 0;
    String intemp = "";
    while(!Serial.available());
    while(Serial.available()){
      char in = Serial.read();
      if (in == ';'){
        char a[] ="   ";
        intemp.toCharArray(a,intemp.length()+1);
        int aback = StrtoHex(a);
        UID[UIDno] = aback;
        intemp = "";
        UIDno ++;
        if (UIDno == 4){
          u8g.firstPage();
          do{
            u8g.setPrintPos(13, 40); // (x,y)
            u8g.print(UID[0],HEX);
            u8g.print(' ');
            u8g.print(UID[1],HEX);
            u8g.print(' ');
            u8g.print(UID[2],HEX);
            u8g.print(' ');
            u8g.print(UID[3],HEX);
          }
          while(u8g.nextPage());
          break;
        }
      }
      else if ((in>=48 && in<=57 ) || (in >= 65 && in <= 70)){
        intemp += in;
      }
      else{
        Serial.println("ERROR");
        while (1){
          u8g.firstPage();
          do{
            u8g.setFont(u8g_font_helvR12);
            u8g.setPrintPos(20, 40);
            u8g.print("ERROR");
            u8g.setFont(u8g_font_6x10);
            u8g.setPrintPos(10, 50);
            u8g.print("Made by Sloth Maker");
          }
          while(u8g.nextPage());
          delay(500);
          
          delay(500);
        }
      }
      delay(10);
    }
  }
  
  
  
  
  Serial.println("READY");
}
