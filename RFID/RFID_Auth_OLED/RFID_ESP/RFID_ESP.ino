#include <SoftwareSerial.h>
SoftwareSerial uno(0, 2);

#include <ESP8266WiFi.h>
String AP_SSID = "Walter Home";
String AP_PSWD = "58629193";

#include "FirebaseESP8266.h"
FirebaseData firebaseData;
#define FIREBASE_HOST "https://rfid-auth-sloth-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "M3GknnMe2xY1LWQ01OCSXHZsLSFdq4f7phEyXKOP"

#include <ESP8266HTTPClient.h>
#define timeURL "http://worldtimeapi.org/api/timezone/Asia/Taipei"

WiFiClient wifiClient;

bool readingCard = false;

String newdata = "";

void setup() {
  uno.begin(9600);
  Serial.begin(9600);

  // Wifi
  WiFi.begin(AP_SSID, AP_PSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //    WiFi.begin(AP_SSID, AP_PSWD);
    Serial.print(".");
    uno.println("Z0");
    serial();
  }
  uno.println("Z1");

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());


  // Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1500 );
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

unsigned long lmillis_05 = 0;
void loop() {
  if ((millis() - lmillis_05 > 500) || lmillis_05 == 0) {
    if (WiFi.status() == WL_CONNECTED)
      uno.println("Z1");
    else
      uno.println("Z0");


    scanRequestCheck();
    lmillis_05 = millis();
  }

  serial();

}
