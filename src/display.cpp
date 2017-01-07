#include "display.h"

/**********************
 * Setup all the pins
 **********************/
void Display::setup() {
  for ( int i = 0; i < numberOfDigits; i++ ) {
    pinMode(digits[i], OUTPUT);
    digitalWrite(digits[i], DigitOff);
  }
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
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
 *  Bitmask 0b01111111 means an 8 on the display,
 *  whereas 0b01110000 means a 7.
 *
 *  The first bit sets the decimal point active.
 *********************************************/
void Display::displayMask(byte digit, int mask) {
  digitalWrite(digit, DigitOn);

  if ( digit == digitWithDecimalPoint ){
    // Activate decimal point with first bit
    mask |= 0b10000000;
  }

  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, mask);
  digitalWrite(LATCH_PIN, HIGH);

  delayMicroseconds(BRIGHTNESS_DELAY + 1);

  turnAllSegmentsOff();

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
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0);
  digitalWrite(LATCH_PIN, HIGH);
}
