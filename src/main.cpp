#include "main.h"
#include "display.h"
#include "dht.h"

dht DHT;
Display display;

#define DHT22_PIN 13

#define TIME_PER_MODE_IN_MILLIS 4000

#define MODE_TEMP     0b01
#define MODE_HUMIDITY 0b10

byte currentMode = MODE_TEMP;
unsigned long modeLastSwitched = 0;

float currentValue() {
  switch(currentMode) {
    case MODE_TEMP:
      return DHT.temperature;
    case MODE_HUMIDITY:
      return DHT.humidity;
    default:
      return 0.0;
  }
}

char letterForMode() {
  switch(currentMode) {
    case MODE_TEMP:
      return 'C';
    case MODE_HUMIDITY:
      return 'H';
  }
  return 'E';
}

void readAndDisplayValue() {
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      for( int timer = 0; timer < 200; timer++ ) {
        display.displayNumber(currentValue() * 10);
        display.displayLetter(digits[0], letterForMode());
      }
      break;
    case DHTLIB_ERROR_CHECKSUM:
      break;
    case DHTLIB_ERROR_TIMEOUT:
      break;
    default:
      break;
  }
}

void setMode() {
  if( millis() - modeLastSwitched < TIME_PER_MODE_IN_MILLIS ) return;

  currentMode = currentMode ^ 0b11;
  modeLastSwitched = millis();
}

void setup() {
  display.digitWithDecimalPoint = digits[2];
  display.setup();
}

void loop() {
  setMode();
  readAndDisplayValue();
}
