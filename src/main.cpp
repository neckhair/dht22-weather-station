#include "main.h"
#include "display.h"
#include "dht.h"

dht DHT;

#define DHT22_PIN 6

void setup() {
  for ( int i = 0; i < numberOfDigits; i++ )  pinMode(digits[i], OUTPUT);
  for ( int i = 0; i < numberOfSegments; i++) pinMode(segments[i], OUTPUT);

  turnAllSegmentsOff();
}

void loop() {
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:

      for( int timer = 0; timer < 200; timer++ ) {
        for ( byte digit = 0; digit < numberOfDigits; digit++) {
          byte figure = extractDigit(DHT.temperature, digit);
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
