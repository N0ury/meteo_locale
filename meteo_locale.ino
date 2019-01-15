#include "LowPower.h"
#include <SoftwareSerial.h>
#define I2C_ADDRESS 0x3C
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define SLEEP_10MINS 75 // Pour un power down de 10 minutes environ
//#define SLEEP_10MINS 3
#define SLEEP_1MINS 7 // Pour des intervalles de 1 minute

#define DHT_POWER 8 // pin pour alimenter le module DHT22
#define ESP8266_POWER 7 // pin pour mettre en veille l'esp8266

/** Broche "DATA" du capteur */
const byte BROCHE_CAPTEUR = 5;

/* Code d'erreur de la fonction readDHT22() */
const byte DHT_SUCCESS = 0;        // Pas d'erreur
const byte DHT_TIMEOUT_ERROR = 1;  // Temps d'attente dépassé
const byte DHT_CHECKSUM_ERROR = 2; // Données reçues erronées

/* Résultat de la fonction readDHT22 */
byte result;

String ssid = "Livebox-nulloses";
String key = "oh_le_beau_melon";

const byte VAL_MAX = 5;
const byte BUF_MAX = 64;

char buf[BUF_MAX];
char val[VAL_MAX];

/*
* On opte de façon arbitraire que le 1 Arduino sera RX et que le 0 Arduino sera TX
* 1 sera donc relié au TX de l'esp8266, et 0 sera relié au RX de l'esp8266
*/
SoftwareSerial esp8266(11, 10); // RX, TX

// Pour le mode debug, il faut relier la pin 9 à la masse
#define debugPin 9
uint8_t debug = false;
SSD1306AsciiWire oled;

