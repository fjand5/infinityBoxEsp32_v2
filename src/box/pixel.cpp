#include "pixel.h"
CRGB mixColor(CRGB a, CRGB b, float percentOfA)
{
  CRGB ret;
  ret.r = percentOfA * (a.r) / 100.0 + (100 - percentOfA) * (b.r) / 100.0;
  ret.g = percentOfA * (a.g) / 100.0 + (100 - percentOfA) * (b.g) / 100.0;
  ret.b = percentOfA * (a.b) / 100.0 + (100 - percentOfA) * (b.b) / 100.0;
  return ret;
}