void serial(){
  byte UID[16];
  if(Serial.available()){
    char in = Serial.read();
    Serial.print(in);
    // start reading card
    if (in == 'R'){
      int UIDno = 0;
      String intemp = "";
      delay(5);
      while(Serial.available()){
        char inC = Serial.read();
        if (inC == ';'){
          char a[] ="   ";
          intemp.toCharArray(a,intemp.length()+1);
          int aback = StrtoHex(a);
          UID[UIDno] = aback;
          intemp = "";
          UIDno ++;
          if (UIDno == 16)
            break;
        }
        else if ((inC>=48 && inC<=57 ) || (inC >= 65 && inC <= 70))
          intemp += inC;
        delay(5);
      }
      for (int i = 0 ; i < 16 ; i++){
        Serial.print(UID[i]);
        Serial.print(" ");
      }
      Serial.println();
      String readingResult = reading(UID);
      Serial.println(readingResult);
      esp.println(readingResult);
      
      delay(1000);
      
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
    
  }

//R10;23;F3;AA;00;00;F3;F2;21;56;23;78;76;B4;03;44;

  if(esp.available()){
    char in = esp.read();
    Serial.print(in);
    // get connection type
    if (in == 'Z'){
      int espInI = esp.parseInt();
      if (espInI == 1){
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
      else if (espInI == 0){
        u8g.firstPage();
        do{
          u8g.setFont(u8g_font_helvR14);
          u8g.setPrintPos(0, 30);
          u8g.print("Please connect");
          u8g.setPrintPos(25, 50);
          u8g.print("to  Wi-Fi");
        }
        while(u8g.nextPage());
      }
      else
        return;
      lmillis_connection = millis();
    }
    // start reading card
    else if (in == 'R'){
      int UIDno = 0;
      String intemp = "";
      delay(5);
      while(esp.available()){
        char inC = esp.read();
        if (inC == ';'){
          char a[] ="   ";
          intemp.toCharArray(a,intemp.length()+1);
          int aback = StrtoHex(a);
          UID[UIDno] = aback;
          intemp = "";
          UIDno ++;
          if (UIDno == 16)
            break;
        }
        else if ((inC>=48 && inC<=57 ) || (inC >= 65 && inC <= 70))
          intemp += inC;
        delay(5);
      }
      for (int i = 0 ; i < 16 ; i++){
        Serial.print(UID[i]);
        Serial.print(" ");
      }
      Serial.println();
      String readingResult = reading(UID);
      Serial.println(readingResult);
      esp.println(readingResult);
      
      delay(1000);
      
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
  }
}
