#include <Arduino.h>

#define FRAMEPERIOD 2000
#define BRIGHTNESS_DELAY 200

#define DIGIT_1 12
#define DIGIT_2 11
#define DIGIT_3 10
#define DIGIT_4 9

#define LATCH_PIN 4
#define CLOCK_PIN 5
#define DATA_PIN 3

const boolean DigitOn = LOW;
const boolean DigitOff = HIGH;
const boolean SegmentOn = HIGH;
const boolean SegmentOff = LOW;

const int digits[] = { DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1 };

const int digitMasks[] = {
  // ABCDEFG
  0b01111110, // 0
  0b00110000, // 1
  0b01101101, // 2
  0b01111001, // 3
  0b00110011, // 4
  0b01011011, // 5
  0b01011111, // 6
  0b01110000, // 7
  0b01111111, // 8
  0b01111011, // 9
};

const char letterMasks[] = {
  0b01001110, // C for Temperature in Celsius
  0b00110111, // H for Humidity in Percent
  0b01001111, // E for errors
};

class Display {
    void displayMask(byte digit, int mask);
    unsigned long extractDigit(unsigned int number, byte digit);
    void turnAllSegmentsOff();

  public:
    const int numberOfSegments = 7;
    const int numberOfDigits = 4;

    byte digitWithDecimalPoint = 0;

    void setup();
    void displayNumber(unsigned int number);
    void displayFigure(byte digit, byte figure);
    void displayLetter(byte digit, char letter);
};
