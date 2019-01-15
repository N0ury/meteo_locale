/**
 * Lit la température et le taux d'humidité mesuré par un capteur DHT22.
 *
 * @param pin Broche sur laquelle est câblée le capteur.
 * @param temperature Pointeur vers la variable stockant la température.
 * @param humidity Pointeur vers la variable stockant le taux d'humidité.
 * @return DHT_SUCCESS si aucune erreur, DHT_TIMEOUT_ERROR en cas de timeout, ou DHT_CHECKSUM_ERROR en cas d'erreur de checksum.
 */
byte readDHT22(byte pin, float* temperature, float* humidity) {
  
  /* Lit le capteur */
  byte data[5];
  byte ret = readDHT(pin, data, 1, 1000);
  
  /* Détecte et retourne les erreurs de communication */
  if (ret != DHT_SUCCESS) 
    return ret;
    
  /* Calcul la vraie valeur de la température et de l'humidité */
  float fh = data[0];
  fh *= 256;
  fh += data[1];
  fh *= 0.1;
  *humidity = fh;
 
  float ft = data[2] & 0x7f;
  ft *= 256;
  ft += data[3];
  ft *= 0.1;
  if (data[2] & 0x80) {
    ft *= -1;
  }
  *temperature = ft;

  /* Ok */
  return DHT_SUCCESS;
}
