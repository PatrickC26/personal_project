void serial(){
  if (Serial.available()){
    char in = Serial.read();
    Serial.println(in);
    if (in == 'T'){
      Serial.println(timeprocess());
    }
    else if (in == 'R'){
      uno.println("R10;23;F3;AA;00;00;F3;F2;21;56;23;78;76;B4;03;44;");
    }
  }

  if (uno.available()){
    char in = uno.read();
    Serial.println(in);
    if (in == 'A'){
      //A08,0a,f4,04,70,14,db,08,f5,01,08,08,1e,32,03,05;a3-59-32-40%
      delay(10);
      String inTemp = "";
      while(uno.available()){
        in = uno.read();
        if (in == '%'){
          Serial.print(inTemp);
          String newScanRequest = firebaseget("request/isNew");
          
//          Serial.println(newScanRequest);
          if (newScanRequest == "1"){ // Add new
            firebaseput("request/isNew", "0" );
            firebaseput("request/data", newdata );
            firebaseput("request/time", timeprocess() );
          }
          else if (newScanRequest == "0"){ // Auth read
            // normal
            if ( firebaseget("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/data") == inTemp.substring(0, inTemp.indexOf(";") )){
              firebaseput("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/time", timeprocess() );
              firebaseput("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/data", newdata );
            }
            // Reopen
            else if (firebaseget("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/data") == "RE"){
              firebaseput("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/time", timeprocess() );
              firebaseput("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/data", newdata );
            }
            // bad data
            else{
              firebaseput("account/" + inTemp.substring(inTemp.indexOf(";") +1, inTemp.length()) + "/badTime", timeprocess() );
            }
          }
          firebaseput("request/scanUID", inTemp.substring(inTemp.indexOf(";") +1, inTemp.length() ));
          readingCard = false;

          firebaseput("request/requestScan", "0" );
        }
        else 
          inTemp += in;
        delay(5);
      }
    }
    else if (in == 'Q'){
      readingCard = false;
    }
  }
}
