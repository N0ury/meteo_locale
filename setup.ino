void setup() { 

  pinMode(debugPin, INPUT_PULLUP);
  
  esp8266.begin(9600);
  delay(500);
  
  debug = !digitalRead(debugPin); // Par défaut l'état est à HIGH:debug=off à cause de la résistance de pull-up interne
  if (debug) {
    Serial.begin(9600);
    Serial.println("Begin setup");
    //Wire.begin();                
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
    oled.setFont(System5x7);
    #if INCLUDE_SCROLLING == 0
    #error INCLUDE_SCROLLING must be non-zero. Edit SSD1306Ascii.h
    #elif INCLUDE_SCROLLING == 1
    // Scrolling is not enable by default for INCLUDE_SCROLLING set to one.
    oled.setScroll(true);
    #else  // INCLUDE_SCROLLING
    // Scrolling is enable by default for INCLUDE_SCROLLING greater than one.
    #endif
    oled.clear();
    oled.println("Begin setup");
  }
  
  /* Place la broche du capteur en entrée avec pull-up */
  pinMode(BROCHE_CAPTEUR, INPUT_PULLUP);

  /* Place la broche d'alimentation du DHT22 en mode OUTPUT */
  pinMode (DHT_POWER, OUTPUT);

  /* Clignotement de début */
  blink(13, 5);

  pinMode(ESP8266_POWER, OUTPUT);  // sets ESP8266_POWER to output
  if (debug) {
    Serial.println("Reveil esp8266  (RST)");
    oled.println("Reveil esp8266 (RST)");
  }
  digitalWrite(ESP8266_POWER, HIGH);  // sets ESP8266_POWER to high (réveil via CH_PD) => reset de l'esp8266

  // Reset de l'esp8266
  esp8266.println("AT+RST");
  delay(3000);
  
  /**
   * Initialisation
   */
  if (debug) {
    Serial.println("envoi commande AT");
    oled.println("envoi commande AT");
  }
  esp8266.println("AT");
  findResponse(500, "OK", 5);

  /**
   * Set Mode CLIENT
   */
  if (debug) {
    Serial.println("Mise en mode client");
    oled.println("Mise en mode client");
  }
  esp8266.println("AT+CWMODE=1");
  findResponse(500, "OK", 5);

  if (debug) {
    Serial.println("Connexion au point d'accès avec SSID et passphrase");
    oled.println("Conn AP (SSID + pass)");
  }
  esp8266.println("AT+CWJAP=\""+ssid+"\",\""+key+"\"");
  findResponse(500, "OK", 5);

  /**
   * Set single connexion
   */
  if (debug) {
    Serial.println("Configuration en mode connexion unique");
    oled.println("Conf conn unique");
  }
  esp8266.println("AT+CIPMUX=0");
  findResponse(500, "OK", 5);
  
  if (debug) {
    Serial.println("Mise en veille de l'esp8266");
    oled.println("Mise en veille esp8266");
  }
  digitalWrite(ESP8266_POWER, LOW);  // set ESP8266_POWER low this takes CH_PD & powers down the ESP

  if (debug) {
    Serial.println("======================== end setup =======================");
    oled.println("End setup");
  }
}

