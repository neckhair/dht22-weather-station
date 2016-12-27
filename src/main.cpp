#include "main.h"
#include "display.h"
#include "dht.h"

dht DHT;

#define DHT22_PIN 6

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
}

void readAndDisplayValue() {
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      for( int timer = 0; timer < 200; timer++ ) {
        for ( byte digit = 1; digit < numberOfDigits; digit++) {
          byte figure = extractDigit(currentValue(), digit);
          displayFigure(digits[digit], figure);
        }
        displayLetter(digits[0], letterForMode());
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
  for ( int i = 0; i < numberOfDigits; i++ )  pinMode(digits[i], OUTPUT);
  for ( int i = 0; i < numberOfSegments; i++) pinMode(segments[i], OUTPUT);

  turnAllSegmentsOff();
}

void loop() {
  setMode();
  readAndDisplayValue();
}
