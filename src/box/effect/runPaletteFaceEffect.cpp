#include "effect.h"
static uint16_t runner = 0;
static uint16_t width = 6;
static uint32_t timer = 0;
static uint32_t speed = 0;

void Effect::runPaletteFaceEffectOnBeat(double val, double freq)
{
  width = val * LED_FACE_COUNT / 100;
  if (width < 6)
    width = 6;
};
void Effect::runPaletteFaceEffectHandle(uint8_t brightness)
{
  ICRGB colors[LED_FACE_COUNT] = {ICRGB(CRGB::Black, EffectName_RunPaletteFace)}; // box.getPixels() + box.getSegmentPosition(sn);

  for (uint16_t i = runner; i < width + runner; i++)
  {
    uint16_t _i;
    if (i >= LED_FACE_COUNT)
    {
      _i = i - LED_FACE_COUNT;
    }
    else
    {
      _i = i;
    }
    colors[_i] = getColorPaletteRing(getPalette(), LED_FACE_COUNT, _i, brightness);
  }

  if (millis() - timer > speed)
  {
    if (width > 6)
    {
      width -= 2;
      speed = 10;
    }
    else
    {
      speed = 75;
    }
    runner++;
    if (runner >= LED_FACE_COUNT)
      runner = 0;
    timer = millis();
  }
  SET_ALL_FACE_COLORS(colors);
};