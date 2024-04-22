#include <ESP8266WiFi.h> 
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>

#define versionID "1.0.1.0119"

// WiFi
const char* WIFI_SSID = "Walter Home";
const char* WIFI_PSWD = "58629193";

// Serial
#include <SoftwareSerial.h>
SoftwareSerial Uno(2, 0);//(RX/TX) // D7-D8


#define timeURL "http://worldtimeapi.org/api/timezone/Asia/Taipei"

#define LINE_TOKEN "a6NHJQHEvWw90e3FlffGrpMYrJWmRSS4czVdgSoi4sv"
