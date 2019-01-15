/**
 * try a HTTP PUT
 */
void sendData(String data) {

  int maxLoops = 5;
  bool result=true;

  if (debug) {
    Serial.println("Reveil esp8266 (RST)");
    oled.println("Reveil esp8266 (RST)");
  }
  digitalWrite(ESP8266_POWER, HIGH);  // sets ESP8266_POWER to high (réveil via CH_PD) => reset de l'esp8266

  result = findResponse(500, "WIFI GOT IP", 10); // On attend la fin du reset
  if (debug) { 
    Serial.print("reset termine:"); Serial.println(result);
    oled.print("reset termine:"); oled.println(result);
  }
  
  /**
   * Connect to web server
   */
  String cmd = "AT+CIPSTART=\"TCP\",\"meteo.dagami.org\",80";
  esp8266.println(cmd);
  result = findResponse(500, "OK", 10);
  if (debug) {
    Serial.print("CIPSTART fait:"); Serial.println(result);
    oled.print("CIPSTART fait:"); oled.println(result);
  }

  /**
   * Send PUT request
   */
  if (result) {
    String cmdPUT = String("PUT /uplink HTTP/1.1\r\n") +
    "Host: meteo.dagami.org\r\n" +
    "Content-Type: application/json\r\n" +
    "Connection: close\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "\r\n" +
    data;
    esp8266.print("AT+CIPSEND=");
    esp8266.println(cmdPUT.length());
    result = findResponse(500, ">", 20);
    if (debug) {
      Serial.print("CIPSEND termine:"); Serial.println(result);
      oled.print("CIPSEND termine:"); oled.println(result);
    }
  
    if (result) {
      esp8266.print(cmdPUT); // print seulement
      result = findResponse(500, "SEND OK", 20);
      if (debug) {
        Serial.print("PUT termine:"); Serial.println(result);
        oled.print("PUT termine:"); oled.println(result);
      }

      while (esp8266.available()) {
        String tmpResp = esp8266.readString();
      }
    }
  }

  /*
   * AT+CIPSTATUS inutile ici car nous n'avons rien d'autre à faire dans tous les cas
   */
   
  /*
   * AT+CIPCLOSE inutile ici car nous avons mis "Connection: close\r\n" dans le PUT
   */
  
  if (debug) {
    Serial.println("Mise en veille de l'esp8266");
    oled.println("Mise en veille esp8266");
  }
  digitalWrite(ESP8266_POWER, LOW);  // set ESP8266_POWER low this takes CH_PD & powers down the ESP
}
