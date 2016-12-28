#include <Arduino.h>

#define FRAMEPERIOD 2000
#define BRIGHTNESS_DELAY 200

#define digit1 7
#define digit2 4
#define digit3 3
#define digit4 9
#define segmentG 8
#define segmentF 5
#define segmentA 6
#define segmentB 2
#define segmentE 12
#define segmentD 11
#define segmentC 10

const boolean DigitOn = LOW;
const boolean DigitOff = HIGH;
const boolean SegmentOn = HIGH;
const boolean SegmentOff = LOW;

const int segments[] = { segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG };
const int digits[] = { digit4, digit3, digit2, digit1 };

const int digitMasks[] = {
// ABCDEFG
  0b1111110, // 0
  0b0110000, // 1
  0b1101101, // 2
  0b1111001, // 3
  0b0110011, // 4
  0b1011011, // 5
  0b1011111, // 6
  0b1110000, // 7
  0b1111111, // 8
  0b1111011, // 9
};

const char letterMasks[] = {
  0b1001110, // C
  0b0110111, // H
};

const int numberOfSegments = 7;
const int numberOfDigits = 4;

unsigned long extractDigit(unsigned int number, byte digit);
void turnAllSegmentsOff();
void displayFigure(byte digit, byte figure);
void displayLetter(byte digit, char letter);
