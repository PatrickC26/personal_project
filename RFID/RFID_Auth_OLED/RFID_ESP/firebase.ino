String firebaseget(String folder){
  if (Firebase.getString(firebaseData,folder)){
    Serial.print(String(folder) + " :");
    String data = firebaseData.stringData();
    Serial.println(data);
    return data;
  }
  else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  return "";
}


void firebaseput(String folder, String data){
  if(Firebase.setString(firebaseData, folder, data)){
    Serial.println(String(folder) + " :" + data + "uploaded");
  }
  else{
    Serial.println("FAILED");
    Serial.println("REASON: " + folder + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}
