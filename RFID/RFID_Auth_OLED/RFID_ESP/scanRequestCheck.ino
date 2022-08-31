void scanRequestCheck(){
//  Serial.println("scan Request Check");
  String scanRequest = firebaseget("request/requestScan");
  if (scanRequest == "1" && !readingCard){
    String outS = "R";
    for (int i = 0 ; i < 16 ; i++){
      int r = random(10, 99);
      outS += String(r);
      outS += ";";
    }
    Serial.println(outS);
    uno.println(outS);
    readingCard = true;
    newdata = outS.substring(1,outS.length() -1);
    newdata.replace(";",",");
  }
  else if (scanRequest == "0" && readingCard){
    uno.println("D%");
  }
}
