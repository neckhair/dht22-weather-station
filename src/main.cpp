#include "main.h"
#include "display.h"

void setup() {
  for ( int i = 0; i < numberOfDigits; i++ )  pinMode(digits[i], OUTPUT);
  for ( int i = 0; i < numberOfSegments; i++) pinMode(segments[i], OUTPUT);

  turnAllSegmentsOff();
}

void loop() {
  for( unsigned int i = 9999; i > 0; i-- ){
    for( int timer = 0; timer < 15; timer++ ) {

      for ( byte digit = 0; digit < numberOfDigits; digit++) {
        byte figure = extractDigit(i, digit);
        displayFigure(digits[digit], figure);
      }

    }
  }
}
