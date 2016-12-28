#include <Arduino.h>

#define FRAMEPERIOD 2000
#define BRIGHTNESS_DELAY 200

#define DIGIT_1 7
#define DIGIT_2 4
#define DIGIT_3 3
#define DIGIT_4 9
#define SEGMENT_G 8
#define SEGMENT_F 5
#define SEGMENT_A 6
#define SEGMENT_B 2
#define SEGMENT_E 12
#define SEGMENT_D 11
#define SEGMENT_C 10
#define DECIMAL_POINT A0

const boolean DigitOn = LOW;
const boolean DigitOff = HIGH;
const boolean SegmentOn = HIGH;
const boolean SegmentOff = LOW;

const int segments[] = { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G };
const int digits[] = { DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1 };

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
