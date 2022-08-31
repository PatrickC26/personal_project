void setup() {
  
  // Setup serial port
  Serial.begin(9600);
  Serial.println();
  
  WiFi.begin(AP_SSID, AP_PSWD);  //Connect to the WiFi network
  Serial.println("Waiting to connect...");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  
  // http server
  server.on("/", user_handeler);
  server.on("/scan", scan_handeler);
  server.on("/reStart", restart_handeler);
  server.on("/add2Found", add2Found_handeler);
  server.on("/dataAmount",  dataAmount_handeler);
  
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  // buzzer
  pinMode(buzzPin,OUTPUT);
  tone(buzzPin, 1000);
  delay(100);
  tone(buzzPin, 0);

  renew();

  Serial.println("ALL SET");


  
}
