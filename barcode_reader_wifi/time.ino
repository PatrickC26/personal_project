void renew(){
  // Get current time
  String serverPath = "http://worldtimeapi.org/api/timezone/Asia/Taipei";

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("UnConnected");
    return;
  }
  
  WiFiClient client;
  HTTPClient http;
  Serial.println("Requesting " + serverPath);
  
  if (!http.begin(client, serverPath)) {
    Serial.printf("[HTTPS] Unable to connect\n");
    return;
  }
  
  int httpCode = http.GET();
  Serial.print("HTTP Response code: ");
  Serial.println(httpCode);
  
  if (httpCode > 0) {
    String payload = http.getString();
    String g_time = payload.substring(payload.indexOf("datetime\":\"" + 5), payload.indexOf("+08:00\","));
    g_time = g_time.substring(6, 25);
    g_time.replace("T", "  ");
    Serial.println(g_time);
    start_Time = g_time;
  }
  http.end();

  for (int i = 0 ; i < 100 ; i++){
    recordData[i] = "";
  }
  for (int i = 0 ; i < 50 ; i++){
    findData[i] = "";
  }
  
  findDataAmount = 0;
  dataAmount = 0;
}
