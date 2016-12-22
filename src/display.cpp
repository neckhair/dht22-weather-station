#include "display.h"

void turnAllSegmentsOff() {
  for( int i = 0; i < numberOfSegments; i++) {
    digitalWrite(segments[i], SegmentOff);
  }
}

void displayFigure(byte digit, byte figure) {
  digitalWrite(digit, DigitOn);

  int mask = masks[figure];

  if( ( mask & 0b1000000 ) > 0 ) digitalWrite(segmentA, SegmentOn);
  if( ( mask & 0b0100000 ) > 0 ) digitalWrite(segmentB, SegmentOn);
  if( ( mask & 0b0010000 ) > 0 ) digitalWrite(segmentC, SegmentOn);
  if( ( mask & 0b0001000 ) > 0 ) digitalWrite(segmentD, SegmentOn);
  if( ( mask & 0b0000100 ) > 0 ) digitalWrite(segmentE, SegmentOn);
  if( ( mask & 0b0000010 ) > 0 ) digitalWrite(segmentF, SegmentOn);
  if( ( mask & 0b0000001 ) > 0 ) digitalWrite(segmentG, SegmentOn);

  delayMicroseconds(BRIGHTNESS_DELAY + 1);

  turnAllSegmentsOff();

  digitalWrite(digit, DigitOff);

  delayMicroseconds(FRAMEPERIOD - BRIGHTNESS_DELAY + 1);
}

unsigned long extractDigit(unsigned int number, byte digit) {
  char numberAsString[4];
  sprintf(numberAsString, "%4d", number);
  char character[] = { numberAsString[digit] };
  return strtoul(character, NULL, 10);
}
