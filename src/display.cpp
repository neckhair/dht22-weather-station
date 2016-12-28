#include "display.h"

void turnAllSegmentsOff() {
  for( int i = 0; i < numberOfSegments; i++) {
    digitalWrite(segments[i], SegmentOff);
  }
}

void displayMask(byte digit, int mask) {
  digitalWrite(digit, DigitOn);

  if( ( mask & 0b1000000 ) > 0 ) digitalWrite(segmentA, SegmentOn);
  if( ( mask & 0b0100000 ) > 0 ) digitalWrite(segmentB, SegmentOn);
  if( ( mask & 0b0010000 ) > 0 ) digitalWrite(segmentC, SegmentOn);
  if( ( mask & 0b0001000 ) > 0 ) digitalWrite(segmentD, SegmentOn);
  if( ( mask & 0b0000100 ) > 0 ) digitalWrite(segmentE, SegmentOn);
  if( ( mask & 0b0000010 ) > 0 ) digitalWrite(segmentF, SegmentOn);
  if( ( mask & 0b0000001 ) > 0 ) digitalWrite(segmentG, SegmentOn);

  digitalWrite(dp, digit == 4);

  delayMicroseconds(BRIGHTNESS_DELAY + 1);

  turnAllSegmentsOff();
  digitalWrite(dp, LOW);

  digitalWrite(digit, DigitOff);

  delayMicroseconds(FRAMEPERIOD - BRIGHTNESS_DELAY + 1);
}

void displayFigure(byte digit, byte figure) {
  int mask = digitMasks[figure];
  displayMask(digit, mask);
}

void displayLetter(byte digit, char letter) {
  int mask;
  switch( letter ) {
    case 'C':
      mask = letterMasks[0];
      break;
    case 'H':
      mask = letterMasks[1];
      break;
  }
  displayMask(digit, mask);
}

unsigned long extractDigit(unsigned int number, byte digit) {
  char numberAsString[4];
  sprintf(numberAsString, "%4d", number);
  char character[] = { numberAsString[digit] };
  return strtoul(character, NULL, 10);
}
