/// @file    Board.ino
/// @brief   Test board
/// @example Blink.ino

#include <FastLED.h>

// Number of leds in strip
#define NUM_LEDS 50

// Command PIN
#define DATA_PIN A2

// Define the array of leds
CRGB leds[NUM_LEDS];

// Segments
/*
      ┌───────────┐
      │     A     │
      └───────────┘
  ┌──┐              ┌──┐
  │  │              │  │
  │F │              │B │
  │  │              │  │
  └──┘ ┌──────────┐ └──┘
       │     G    │
       └──────────┘
  ┌──┐              ┌──┐
  │  │              │  │
  │E │              │C │
  │  │              │  │
  └──┘              └──┘
      ┌────────────┐
      │      D     │
      └────────────┘
*/

#define SEG_LENGHT 3

// Define 7 segments
/*
unsigned short SEG_A[SEG_LENGHT] = { 36, 37, 38 };
unsigned short SEG_B[SEG_LENGHT] = { 33, 34, 35 };
unsigned short SEG_C[SEG_LENGHT] = { 47, 48, 49 };
unsigned short SEG_D[SEG_LENGHT] = { 27, 28, 29 };
unsigned short SEG_E[SEG_LENGHT] = { 43, 44, 45 };
unsigned short SEG_F[SEG_LENGHT] = { 39, 40, 41 };
unsigned short SEG_G[SEG_LENGHT] = { 31, 32, 42 };
*/

#define NUM_LED_PER_SEGMENT 3

#define NUM_SEGMENTS 7

unsigned short ledsForSegments[NUM_SEGMENTS][NUM_LED_PER_SEGMENT] = {
  { 36, 37, 38 },  // A
  { 33, 34, 35 },  // B
  { 27, 28, 29 },  // C
  { 47, 48, 49 },  // D
  { 43, 44, 45 },  // E
  { 39, 40, 41 },  // F
  { 31, 32, 42 },  // G
};

bool segmentsMap[10][NUM_SEGMENTS] = {
  // a, b, c, d, e, f, g
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 }   // 9
};

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
}

bool first_run = 1;
short count = 0;
void loop() {
  if (first_run) {
    delay(500);
    for (int i = 0; i < 7; i++) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      for (short j = 0; j < 3; j++) {
        leds[ledsForSegments[i % 10][j]] = CRGB::Red;
      }
      FastLED.show();

      delay(1000);
    }
    first_run = 0;
  } else {
    print(count);
    count++;
    delay(1000);
  }
}

void print(short num) {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  if (num > 0) {
    // get corresponding segments
    bool *segments = segmentsMap[num % 10];
    for (short i = 0; i < 7; i++) {
      // for each segments enabled
      if (segments[i]) {
        //
        for (short j = 0; j < NUM_LED_PER_SEGMENT; j++) {
          leds[ledsForSegments[i][j]] = CRGB::Red;
        }
      }
    }
  }

  FastLED.show();
}