#pragma once
#include <Arduino.h>
#include <WS2812FX.h>
float mix(float a, float b, float t);

float step(float e, float x);
float fract(float x);

// h: 0->1
// s: 0->1
// v: 0->255
void rgb2hsv(uint32_t rgbColor, float *hsv);
void hsv2rgb(float h, float s, float b, uint32_t *rgb);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheelColor(WS2812FX *leds, byte WheelPos);

void blendRange(WS2812FX *leds, int start, int stop, uint32_t color, uint8_t ratio = 128);
uint16_t countZeroPixel(WS2812FX *leds, int start, int stop);
float calcTotalValuePixel(WS2812FX *leds, int start, int stop);

int setPixelInSegment(WS2812FX *leds, WS2812FX::Segment *_seg, int index, uint32_t color);
void clearPixelInSegment(WS2812FX *leds, WS2812FX::Segment *_seg);