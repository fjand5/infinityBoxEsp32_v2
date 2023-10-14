#include "effect.h"
static uint16_t runner = 0;
static int16_t width = 0;
static int16_t noBeatWidth = 0;
static int16_t lastMax = 0;
static int16_t lastMaxSig = 1;
static uint32_t timer = 0;
static uint32_t lastMaxtTimer = 0;
static uint32_t lastBeatTime = 0;
static uint32_t speed = 20;
static ICRGB colors[LED_SEGMENT_COUNT] = {ICRGB(CRGB::Black, EffectName_VUMeterSegment)};
static uint16_t numOfNotZero = 0;

void Effect::vUMeterHalfSegmentEffectOnBeat(double val, double freq)
{
  if (val < 5)
    return;
  width = val * LED_HALF_SEGMENT_COUNT / 100;
  if (lastMax < width)
  {
    lastMax = width;
  }
  lastBeatTime = millis();
};
void noSoundHandle(Effect *effect, uint8_t brightness)
{

  for (uint8_t i = 0; i < LED_HALF_SEGMENT_COUNT; i++)
  {
    if (i <= width || i == lastMax)
    {
      colors[i] = effect->getColorPaletteRing(effect->getPalette(), LED_HALF_SEGMENT_COUNT, 0, i + runner, brightness);
    }
    else
    {
      colors[i] = ICRGB::Black;
    }
  }
  for (uint8_t i = LED_HALF_SEGMENT_COUNT; i < LED_SEGMENT_COUNT; i++)
  {
    colors[i] = colors[LED_SEGMENT_COUNT - 1 - i];
  }

  if (millis() - lastMaxtTimer > speed * 3)
  {
    lastMaxtTimer = millis();
    lastMax--;

    if (lastMax <= width)
    {
      lastMax = LED_HALF_SEGMENT_COUNT;
      width++;
      if (width == LED_HALF_SEGMENT_COUNT)
      {
        width = 0;
      }
    };
  }
  if (millis() - timer > speed * 2)
  {
    runner++;

    timer = millis();
  }
}
void withSoundHandle(Effect *effect, uint8_t brightness)
{
  for (uint8_t i = 0; i < LED_HALF_SEGMENT_COUNT; i++)
  {
    if (i <= width || i == lastMax)
    {
      colors[i] = effect->getColorPaletteRing(effect->getPalette(), LED_HALF_SEGMENT_COUNT, 0, i + runner, brightness);
    }
    else
    {
      colors[i] = ICRGB::Black;
    }
  }
  for (uint8_t i = LED_HALF_SEGMENT_COUNT; i < LED_SEGMENT_COUNT; i++)
  {
    colors[i] = colors[LED_SEGMENT_COUNT - 1 - i];
  }

  if (millis() - lastMaxtTimer > speed * 3)
  {
    lastMaxtTimer = millis();
    if (lastMax > 0)
      lastMax--;
  }

  if (millis() - timer > speed)
  {
    if (width > LED_HALF_SEGMENT_COUNT / 3)
      runner++;
    if (width >= 0)
      width--;
    timer = millis();
  }
}
void Effect::vUMeterHalfSegmentEffectHandle(uint8_t brightness)
{
  if (millis() - lastBeatTime > 1000)
  {
    noSoundHandle(this, brightness);
  }
  else
  {
    withSoundHandle(this, brightness);
  }

  SET_ALL_SEGMENT_COLORS(colors);
};