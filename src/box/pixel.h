#pragma once
#include <FastLED.h>

CRGB mixColor(CRGB a, CRGB b, float percentOfA);
struct ICRGB : CRGB
{
  int8_t i = 0;
  ICRGB()
  {
    r = 0;
    g = 0;
    b = 0;
    i = 0;
  };
  ICRGB(uint8_t ir, uint8_t ig, uint8_t ib, uint8_t ii)
  __attribute__((always_inline))
  {
    r = ir;
    g = ig;
    b = ib;
    i = ii;
  }
  ICRGB(CRGB color)
  __attribute__((always_inline))
  {
    ICRGB(color, 0);
  };
  ICRGB(CRGB color, int8_t ii)
  __attribute__((always_inline))
  {
    r = color.r;
    g = color.g;
    b = color.b;
    i = ii;
  }
  inline ICRGB &operator=(const CRGB color) __attribute__((always_inline))
  {
    r = color.r;
    g = color.g;
    b = color.b;
    return *this;
  }
  inline CRGB &setValue(uint8_t val) __attribute__((always_inline))
  {
    hsv2rgb_rainbow(CHSV(255, 255, val), *this);
    return *this;
  }
  inline CRGB &fromHSV(uint8_t h, uint8_t s, uint8_t v) __attribute__((always_inline))
  {
    hsv2rgb_rainbow(CHSV(h, s, v), *this);
    return *this;
  }
  inline CRGB &fromHSV(CHSV hsv) __attribute__((always_inline))
  {
    hsv2rgb_rainbow(hsv, *this);
    return *this;
  }
  inline CRGB &fromString(String hexString) __attribute__((always_inline))
  {
    CRGB color(strtoul(hexString.c_str(), nullptr, 16));
    r = color.r;
    g = color.g;
    b = color.b;
    return *this;
  }
  String toString()
  {

    char hexString[7];
    utoa(r << 16 | g << 8 | b, hexString, 16);
    String ret(hexString);
    while (ret.length() < 6)
    {
      ret = "0" + ret;
    }
    return ret;
  }

  CRGB getColorWithoutIndex()
  {
    return CRGB(r, g, b);
  }
};
