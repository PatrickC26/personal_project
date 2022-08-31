void add2Found_handeler() {
  if (!server.hasArg("plain")){ //Check if body received
    server.send(200, "text/plain", "");
    return;
  }
  String getData = server.arg("plain") + ",";

  for (int i = 0 ; true ; i++){
    if (findDataAmount >= 49){
      
      String temp_findData[50] ;
      for(int i = 0 ; i < 49 ; i++){
        temp_findData[i] = findData[i+1];
      }
      findData[49] = getData.substring(0,getData.indexOf(","));
      getData = getData.substring(getData.indexOf(",")+1 , getData.length());
      
      String message = "add2Found received:\n";
             message += findData[49];
             message += "\n";
    }
    else{
      findData[findDataAmount] = getData.substring(0,getData.indexOf(","));
      getData = getData.substring(getData.indexOf(",")+1 , getData.length());
    
      String message = "add2Found received:\n";
             message += findData[findDataAmount];
             message += "\n";
    }
    findDataAmount++;
    if (getData.indexOf(",") < 0)
      break;
  }
  server.send(200, "text/plain", "");

  for (int i = 0 ; i < findDataAmount ; i ++){
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(findData[i]);
  }
}
