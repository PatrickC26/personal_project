#include "LowPower.h"
bool statusB = 0;
// 0 -> with error or first on
// 1 -> with returning on

// status light
#define statusLightPin 8
int  espConnection = 0;

// esp
#include <SoftwareSerial.h>
SoftwareSerial esp  (7, 6); // 10=> RX ,11=> TX
unsigned long ESP_timeout = 0;
String ESP_Value = "";
#define ESP_EN 5

// previous Send
unsigned long preMillis = 0;

// temperature
#define ThermistorPin1  A0
#define ThermistorPin2  A1
#define ThermistorPin3  A2
unsigned long lastDetectMillis = 0;

//// DHT
//#include <DHT.h>
//#define dhtPin 7      //讀取DHT11 Data
//#define dhtType DHT11 //選用DHT11  
//DHT dht(dhtPin, dhtType);

//mode
#define CLEAR 0
#define ESP_WORK 1
#define ESP_ERROR 2
#define FRIDGE_ERROR 3
#define FRIDGE_OK 4
int currentMode = 0;

#define RED 8
#define GREEN 9
#define BLUE 10
