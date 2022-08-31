String timeprocess(){
  String nowtime = esp8266Http(timeURL);
  String temp = nowtime.substring(nowtime.indexOf("datetime")+11,nowtime.indexOf("+08:00\""));
  String nowh = temp.substring(temp.indexOf("T")+1,temp.indexOf("."));
  String nowdate = temp.substring(0,temp.indexOf("T"));
  return (nowdate + " " + nowh);
}

String esp8266Http(String URL){
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient httpClient;
   
    httpClient.begin(wifiClient,URL); 
    Serial.print("URL: "); Serial.println(URL);
   
    int httpCode = httpClient.GET();
    Serial.print("Send GET request to URL: ");
    Serial.println(URL);
    
    if (httpCode == HTTP_CODE_OK) {
      String responsePayload = httpClient.getString();
      Serial.println("Server Response Payload: ");
      Serial.println(responsePayload);
      httpClient.end();
      return responsePayload;
    } 
    else {
      Serial.println("Server Respose Code：");
      Serial.println(httpCode);
      httpClient.end();
      return "";
    }
  }
  return "";
}
