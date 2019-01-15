 char* readDATA() {
  float temperature, humidity;
 
  digitalWrite (DHT_POWER, HIGH); // On met le DHT22 sous tension
  delay(2000); // On attend un peu que le DHT22 soit sous tension
               // Attention, il faut au minimum 1,5 secondes
    
  /* Lecture de la température et de l'humidité, avec gestion des erreurs */
  result = readDHT22(BROCHE_CAPTEUR, &temperature, &humidity);
  
  digitalWrite (DHT_POWER, LOW); // On remet hors tension le DHT22


  /* Traitement du résultat */
  switch (result) {
  case DHT_SUCCESS: 

    // La ligne suivante ne sert que pour un debugging (clignotement de la led 13 2 fois)
    //blink(13, 2); // clignotement après lecture OK

    /* Construction du résultat avec la température et le taux d'humidité */
    strcpy_P(buf, (const char*) F("{\"temperature\":\""));
    dtostrf(temperature, 4, 1, val);
    strcat(buf, val);
    strcat_P(buf, (const char*) F("\",\"humidite\":\""));
    dtostrf(humidity, 4, 1, val);
    strcat(buf, val);
    strcat_P(buf, (const char*) F("\"}"));
    break;
 
  case DHT_TIMEOUT_ERROR: 
    if (debug) Serial.println(F("Pas de reponse !")); 
    break;
 
  case DHT_CHECKSUM_ERROR: 
    if (debug) Serial.println(F("Pb de communication !")); 
    break;
  }
  
  // Arrêt I2C (à conserver)
  TWCR &= ~(bit(TWEN) | bit(TWIE) | bit(TWEA));
  twi_disable();

  return buf;
}

void twi_disable(void)
{
  // disable twi module, acks, and twi interrupt
  TWCR &= ~(_BV(TWEN) | _BV(TWIE) | _BV(TWEA));

  // deactivate internal pullups for twi.
  digitalWrite(SDA, 0);
  digitalWrite(SCL, 0);
}
