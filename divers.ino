void blink(uint8_t pin, uint8_t times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(1000);
  }
}

bool findResponse(int duration, char *text, int maxLoops) {
  bool done = false;

  done = esp8266.find(text);
  int currentLoop = 0;
  while(!done){
    delay(duration);
    done = esp8266.find(text);
    if(currentLoop >= maxLoops){
      break;
    }
    currentLoop++;
  }
  return done;
}
