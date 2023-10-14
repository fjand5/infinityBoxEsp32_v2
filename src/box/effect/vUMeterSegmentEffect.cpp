#include "effect.h"
static uint16_t runner = 0;
static int16_t width = 0;
static int16_t noBeatWidth = 0;
static int16_t lastMax = 0;
static uint32_t timer = 0;
static uint32_t lastMaxtTimer = 0;
static uint32_t lastBeatTime = 0;
static uint32_t speed = 20;
static ICRGB colors[LED_SEGMENT_COUNT] = {ICRGB(CRGB::Black, EffectName_VUMeterSegment)};
static uint16_t numOfNotZero = 0;

void Effect::vUMeterSegmentEffectOnBeat(double val, double freq)
{
  if (val < 5)
    return;
  numOfNotZero = 0;
  noBeatWidth = 0;

  width = val * LED_SEGMENT_COUNT / 100;
  if (lastMax < width)
  {
    lastMax = width;
  }
  lastBeatTime = millis();
};
void Effect::vUMeterSegmentEffectHandle(uint8_t brightness)
{
  if (millis() - lastBeatTime > 1000)
  {
    if (lastMax <= noBeatWidth)
    {
      lastMax = LED_SEGMENT_COUNT;
      noBeatWidth++;
    }
    if (noBeatWidth >= LED_SEGMENT_COUNT)
    {
      numOfNotZero = 0;
      for (uint8_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        colors[i].fadeToBlackBy(2);
        if (operator!=(colors[i], CRGB::Black))
        {
          numOfNotZero++;
        }
      }
      if (numOfNotZero == 0)
        noBeatWidth = 0;
    }
    else
    {
      for (uint8_t i = 0; i < LED_SEGMENT_COUNT; i++)
      {
        if (i <= noBeatWidth || i == lastMax)
        {
          colors[i] = getColorPaletteRing(getPalette(), LED_SEGMENT_COUNT, 0, i + runner, brightness);
        }
        else
        {
          colors[i] = ICRGB::Black;
        }
      }
    }
  }
  else
  {
    for (uint8_t i = 0; i < LED_SEGMENT_COUNT; i++)
    {
      if (i <= width || i == lastMax)
      {
        colors[i] = getColorPaletteRing(getPalette(), LED_SEGMENT_COUNT, 0, i + runner, brightness);
      }
      else
      {
        colors[i] = ICRGB::Black;
      }
    }
  }

  if (millis() - lastMaxtTimer > speed * 3)
  {
    lastMaxtTimer = millis();
    if (lastMax > 0)
      lastMax--;
  }

  if (millis() - timer > speed)
  {
    if (width > LED_SEGMENT_COUNT / 3)
      runner++;
    if (width >= 0)
      width--;
    timer = millis();
  }
  SET_ALL_SEGMENT_COLORS(colors);
};