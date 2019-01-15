void loop() {
  int j = 0;
  int iter = 0;

  /* On lit les données du DHT22 */
  String data = readDATA();
  if (debug) {
    Serial.print("data="); Serial.println(data);
    oled.print("data="); oled.println(data);
  }

  // Envoi des données au serveur web
  sendData(data);

  if (debug) {
    // Les flush sont indispensables car pb si on entre dans le LowPower alors que les i/o ne sont pas finies
    Serial.println("On dort"); Serial.println("===================="); Serial.flush();
    oled.println("On dort"); oled.println("====================");
  }


  /* On dort 10 minutes (8*75sec=600sec*/
  for (int i = 0; i < SLEEP_10MINS; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    j++;
    if (j >= SLEEP_1MINS) {
      iter++;
      // Chaque minute, on vérifie si le mode debug a été activé/désactivé
      uint8_t debugNew = !digitalRead(debugPin);
      if (debugNew != debug) {
        debug = debugNew;
        if (debug) {
          Serial.begin(9600);
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
        } else {
          Serial.end();
        }
        oled.clear();
      }
      if (debug) {
        Serial.print (iter); Serial.println(":On passe 1 minute..."); Serial.flush();
        oled.print (iter); oled.println(":On passe 1 minute");
      }
      j = 0;
    }
  }
  if (debug) {
    Serial.println("On se reveille"); Serial.flush();
    oled.println("On se reveille");
  }
}
