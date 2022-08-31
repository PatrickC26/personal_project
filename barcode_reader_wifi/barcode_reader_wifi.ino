#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Set AP credentials
String AP_SSID = "Walter Home";
String AP_PSWD = "58629193";
IPAddress local_IP(192,168,68,125);
IPAddress gateway(192,168,68,125);
IPAddress subnet(255,255,255,0);

// buzzer
#define buzzPin 13

ESP8266WebServer server(80);

WiFiServer serverW(80);

//Html Text
String htmltext = "";
unsigned long lcurrentTime = 0;

//reset func
void(* resetFunc) (void) = 0;

//data
String start_Time = "";
String findData[50];
int findDataAmount = 0;
String recordData[100];
int dataAmount = 0;


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void loop() {
  server.handleClient();

  WiFiClient client = serverW.available();
  if (!client)
    return;
  String request = client.readStringUntil('\r');
  Serial.println(request);
}
