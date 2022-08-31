// OLED
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  //0.96"

// Software serial
#include <SoftwareSerial.h>
SoftwareSerial esp(6,7);

// RFID
#include <SPI.h>
#include <MFRC522.h>     // 引用程式庫
#define RST_PIN   10        // 讀卡機的重置腳位
#define SS_PIN    A0         // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
MFRC522::MIFARE_Key key;

// Duplicator UID
byte UID[4];
bool state = false; //false -> read  true -> write

// make string to hex int
int StrtoHex(char str[]){
  return (int) strtol(str, 0, 16);
}

// variables
unsigned long lmillis_connection = 0;


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
