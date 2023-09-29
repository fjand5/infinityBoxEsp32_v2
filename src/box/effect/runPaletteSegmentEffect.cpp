#include "effect.h"
static uint16_t runner = 0;
static uint16_t width = 3;
static uint32_t timer = 0;
static uint32_t speed = 50;

void Effect::runPaletteSegmentEffectOnBeat(double val, double freq)
{
  width = val * LED_SEGMENT_COUNT / 100;
  if (width < 3)
    width = 3;
};
void Effect::runPaletteSegmentEffectHandle(uint8_t brightness)
{
  ICRGB colors[LED_SEGMENT_COUNT] = {ICRGB(CRGB::Black, EffectName_RunPaletteSegment)}; // box.getPixels() + box.getSegmentPosition(sn);

  for (uint16_t i = runner; i < width + runner; i++)
  {
    uint16_t _i;
    if (i >= LED_SEGMENT_COUNT)
    {
      _i = i - LED_SEGMENT_COUNT;
    }
    else
    {
      _i = i;
    }
    colors[_i] = getColorPaletteRing(getPalette(), LED_SEGMENT_COUNT, _i, brightness);
  }

  if (millis() - timer > speed)
  {
    if (width > 3)
    {
      width -= 1;
      speed = 20;
    }
    else
    {
      speed = 75;
    }


    runner++;
    if (runner >= LED_SEGMENT_COUNT)
      runner = 0;
    timer = millis();
  }
  SET_ALL_SEGMENT_COLORS(colors);
};