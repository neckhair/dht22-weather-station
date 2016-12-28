#include "display.h"

/**********************
 * Setup all the pins
 **********************/
void Display::setup() {
  for ( int i = 0; i < numberOfDigits; i++ )  pinMode(digits[i], OUTPUT);
  for ( int i = 0; i < numberOfSegments; i++) pinMode(segments[i], OUTPUT);
  pinMode(DECIMAL_POINT, OUTPUT);
}

/*********************************************
 * Display the bitmask on the specified digit
 *     A
 *    ___
 * F \ G \ B
 *   \---|
 * E \   \ C
 *    ---
 *     C
 *            ABCDEFG
 *  Bitmask 0b1111111 means an 8 on the display,
 *  whereas 0b1110000 means a 7.
 *********************************************/
void Display::displayMask(byte digit, int mask) {
  digitalWrite(digit, DigitOn);

  if( ( mask & 0b1000000 ) > 0 ) digitalWrite(SEGMENT_A, SegmentOn);
  if( ( mask & 0b0100000 ) > 0 ) digitalWrite(SEGMENT_B, SegmentOn);
  if( ( mask & 0b0010000 ) > 0 ) digitalWrite(SEGMENT_C, SegmentOn);
  if( ( mask & 0b0001000 ) > 0 ) digitalWrite(SEGMENT_D, SegmentOn);
  if( ( mask & 0b0000100 ) > 0 ) digitalWrite(SEGMENT_E, SegmentOn);
  if( ( mask & 0b0000010 ) > 0 ) digitalWrite(SEGMENT_F, SegmentOn);
  if( ( mask & 0b0000001 ) > 0 ) digitalWrite(SEGMENT_G, SegmentOn);

  digitalWrite(DECIMAL_POINT, digit == digitWithDecimalPoint);

  delayMicroseconds(BRIGHTNESS_DELAY + 1);

  turnAllSegmentsOff();
  digitalWrite(DECIMAL_POINT, LOW);

  digitalWrite(digit, DigitOff);

  delayMicroseconds(FRAMEPERIOD - BRIGHTNESS_DELAY + 1);
}

/*********************************************
 * Displays a number
 *********************************************/
void Display::displayNumber(unsigned int number) {
    for ( byte digit = 1; digit < numberOfDigits; digit++) {
      byte figure = extractDigit(number, digit);
      displayFigure(digits[digit], figure);
    }
}

/************************ PRIVATE ********************/

/*********************************************
 * Displays a single figure
 *********************************************/
void Display::displayFigure(byte digit, byte figure) {
  int mask = digitMasks[figure];
  displayMask(digit, mask);
}

/*********************************************
 * Displays one of the defined letters
 *********************************************/
void Display::displayLetter(byte digit, char letter) {
  int mask;
  switch( letter ) {
    case 'C':
      mask = letterMasks[0];
      break;
    case 'H':
      mask = letterMasks[1];
      break;
    case 'E':
      mask = letterMasks[2];
      break;
  }
  displayMask(digit, mask);
}

/***************************************************
 * Helper method to extract one digit from a number
 ***************************************************/
unsigned long Display::extractDigit(unsigned int number, byte digit) {
  char numberAsString[4];
  sprintf(numberAsString, "%4d", number);
  char character[] = { numberAsString[digit] };
  return strtoul(character, NULL, 10);
}

void Display::turnAllSegmentsOff() {
  for( int i = 0; i < numberOfSegments; i++) {
    digitalWrite(segments[i], SegmentOff);
  }
}
