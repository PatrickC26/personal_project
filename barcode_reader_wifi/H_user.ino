void user_handeler() {
server.send(200, "text/html", html_wrapping());

}

String html_wrapping(){
    String content = "";
  content = content + 
"<!DOCTYPE html>\n"
+ "<html lang=\"en\">\n"
+ "    <head>\n"
+ "        <meta charset=\"UTF-8\" />\n"
+ "        <meta name=\"format-detection\" content=\"telephone=no\">"
+ "        <title>樹懶工作室｜sloth workshop</title>\n"
+ "        <link rel=\"icon\" href=\"https://patrickc26.github.io/slothMaker-notify/root/ftp/logo/color_100.png\">\n"
+ "    </head>\n"
+ "    <body>\n"
+ "        <center>\n"
+ "            <h1>\n"
+ "                Barcode Scanner\n"
+ "            </h1>\n"
+ "            \n"
+ "            \n"
+ "            <br>\n"
+ "            \n"
+ "            <form>\n"
+ "            To find Serial : <input class=\"editor\" id \"T_name\" type=\"text\" name=\"name\">\n"
+ "                <button type=\"button\" name=\"button\" id=\"button\" onclick=\"load();\" >確定</button>\n"
+ "            </form>\n"
+ "            <br>\n"
+ "          \n"
+ "            <h3>\n";
  for (int i = dataAmount -1 ; i >= 0 ; i--){
    if (i > 99 )
      i = 99;
    content += "                <P style = \"color:";
    
    boolean data_Found = false;
    for (int j = findDataAmount -1 ; j >= 0 ; j--){
//      Serial.print("recordData : ");
//      Serial.println(recordData[i]);
//      Serial.print("findData : ");
//      Serial.println(findData[j]);
      if (recordData[i] == findData[j]){
        data_Found = true;
        break;
      }
    }
    
    if (data_Found)
      content += "red";
    else
      content += "black";
      
    content += "\">\n                ";
    content += String(i) + " . " + recordData[i];
    content += "\n                </p>\n";
  }
content = content + 
"            </h3>\n"
+ "\n"
+ "            <br>\n"
+ "\n"
+ "            <h4>\n"
+ "                Server Start Time : " + start_Time + "\n"
+ "            </h4>\n"
+ "            \n"
+ "            <button type=\"button\" name=\"button\" id=\"button\" onclick=\"restart();\" > Restart Server </button>\n"
+ "            <h5>\n"
+ "                © 樹懶工作室 sloth workshop 2022\n"
+ "            </h5>\n"
+ "            <img src=\"https://patrickc26.github.io/slothMaker-notify/root/ftp/logo/color_500.png\" alt=\"Sloth Maker\" style=\"width:50px;height:50px;\">"
+ "            \n"

+ "          \n"
+ "          \n"
+ "      </center>\n"
+ "  </body>\n"
+ "  \n"
+ "\n"


+ "  <script>\n"
+ "        \n"
+ "    class values {\n"
+ "        static dataAmount = \"\"\n"
+ "    }\n"
+ "      \n"
+ " values.dataAmount = firebaseGET(\"dataAmount\");"
+ "    var t=setInterval(runFunction,3000);\n"
+ "\n"
+ "    function runFunction(){\n"
+ "        if (values.dataAmount != firebaseGET(\"dataAmount\"))\n"
+ "            location.reload();\n"
+ "        console.log(\"reload\");\n"
+ "    }\n"
+ "    \n"
+ "    function load(){\n"
+ "        try{\n"
+ "            var innerS = String(document.querySelector('.editor').value);\n"
+ "            if (innerS != null && innerS != \"\"){\n"
+ "                console.log(innerS);\n"
+ "                firebasePUT(\"add2Found\", innerS);\n"
+ "                window.alert(\"成功登錄\");\n"
+ "                location.reload();\n"
+ "            }\n"
+ "            else{\n"
+ "                window.alert(\"名字不可空白\");\n"
+ "            }\n"
+ "        }\n"
+ "        catch(Exception){\n"
+ "            window.alert(\"名字不可空白，或特殊符號\");\n"
+ "        }\n"
+ "    }\n"
+ "    \n"
+ "    \n"
+ "    function restart(){\n"
+ "      firebasePUT(\"reStart\", \"1\");\n"
+ "      location.reload();\n"
+ "    }\n"
+ "    \n"
+ "      \n"
+ "    function firebaseGET(dic) {\n"
+ "        let url= \"http://192.168.68.125/\" + dic;\n"
+ "        var time = 0;\n"
+ "        do{\n"
+ "            var xmlHttp = new XMLHttpRequest();\n"
+ "            xmlHttp.open( \"GET\", url, false ); // false for synchronous request\n"
+ "            xmlHttp.send( null );\n"
+ "            console.log( xmlHttp.responseText);\n"
+ "            var inS = xmlHttp.responseText;\n"
+ "            return inS;\n"
+ "            time++;\n"
+ "        }while(xmlHttp.status != 200 && time <= 5)\n"
+ "        \n"
+ "        if (time > 4){\n"
+ "            window.alert(\"登錄失敗，請重新登錄\\nerr code : GET - \" + response.status);\n"
+ "            window.location.href = redirectURL;\n"
+ "        }\n"
+ "        return \"\";\n"
+ "    }\n"
+ "      \n"
+ "      \n"
+ "    function firebasePUT(dic , text) {\n"
+ "        let url= \"http://192.168.68.125/\" + dic;\n"
+ "        var time = 0;\n"
+ "        var backB = false;\n"
+ "        \n"
+ "        while(time <= 5){\n"
+ "            time ++;\n"
+ "            fetch(url,{\n"
+ "                method: 'PUT',\n"
+ "                header: {\"plain\": \"plain\"},\n"
+ "                body: text\n"
+ "            })\n"
+ "            .then(response => {\n"
+ "                console.log('response.status: ', response.status);\n"
+ "                if (response.status == 200 ){\n"
+ "                    backB =  true;\n"
+ "                    time = 9;\n"
+ "                }\n"
+ "                else if (time > 5){\n"
+ "                    window.alert(\"訊息傳送失敗，請再試一次\\nerr code : PUT - \" + response.status);\n"
+ "                    time = 9;\n"
+ "                }\n"
+ "            });\n"
+ "            return backB;\n"
+ "        }\n"
+ "        return false;\n"
+ "    }\n"
+ "      \n"
+ "      \n"
+ "  </script>\n"
+ "</html>\n"
;


return content;
}
