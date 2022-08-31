void scan_handeler() {
  if (!server.hasArg("plain")){ //Check if body received
    server.send(200, "text/plain", "");
    return;
  }

  if (dataAmount >= 99){
    
    for(int i = 0 ; i < 99 ; i++){
      recordData[i] = recordData[i+1];
    }
    recordData[99] = server.arg("plain");
    
    String message = "Scanner received:\n";
           message += recordData[99];
           message += "\n";

    
  }
  else{
    recordData[dataAmount] = server.arg("plain");
  
    String message = "Scanner received:\n";
           message += recordData[dataAmount];
           message += "\n";
  
  }
  dataAmount++;
   

  server.send(200, "text/plain", "");
  tone(buzzPin, 1000);
  delay(100);
  tone(buzzPin, 0);
}
