#include <Arduino.h>

#define FRAMEPERIOD 2000
#define BRIGHTNESS_DELAY 200

#define digit1 7
#define digit2 11
#define digit3 12
#define digit4 13
#define segmentG 2
#define segmentF 3
#define segmentA 4
#define segmentB 5
#define segmentE 8
#define segmentD 9
#define segmentC 10

const boolean DigitOn = LOW;
const boolean DigitOff = HIGH;
const boolean SegmentOn = HIGH;
const boolean SegmentOff = LOW;

const int segments[] = { segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG };
const int digits[] = { digit4, digit3, digit2, digit1 };

const int masks[] = {
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
