#include "main.h"
#include "display.h"
#include "dht.h"

dht DHT;

#define DHT22_PIN 6
#define MODE_SWITCH_PIN A0

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

void readAndDisplayValue() {
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      for( int timer = 0; timer < 200; timer++ ) {
        for ( byte digit = 0; digit < numberOfDigits; digit++) {
          byte figure = extractDigit(currentValue(), digit);
          displayFigure(digits[digit], figure);
        }
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
  unsigned int modeSwitch = digitalRead(MODE_SWITCH_PIN);

  if( modeSwitch == LOW) return;
  if( millis() - modeLastSwitched < 200 ) return; // Switch only every x millis

  currentMode = currentMode ^ 0b11;
  modeLastSwitched = millis();
}

void setup() {
  for ( int i = 0; i < numberOfDigits; i++ )  pinMode(digits[i], OUTPUT);
  for ( int i = 0; i < numberOfSegments; i++) pinMode(segments[i], OUTPUT);

  pinMode(MODE_SWITCH_PIN, INPUT);

  turnAllSegmentsOff();
}

void loop() {
  setMode();
  readAndDisplayValue();
}
