void setup(){
  // Serial
  Serial.begin(9600);
  Serial.println("\n\n-------------------------------------\nConnecting to Wi-Fi");
  delay(50);

  // wifi connecting
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // LINE
  LINE.setToken(LINE_TOKEN);

  // pins
  pinMode(0,INPUT_PULLUP);
  pinMode(2,OUTPUT);
}
