#include "effect.h"
static uint16_t runner = 0;
static uint16_t width = 3;
static uint32_t timer = 0;
static uint32_t speed = 250;
static uint16_t numOfZero = 0;

static ICRGB colors[LED_SEGMENT_COUNT] = {ICRGB(CRGB::Black, EffectName_RunPaletteSegment)}; // box.getPixels() + box.getSegmentPosition(sn);

void Effect::starEffectOnBeat(double val, double freq)
{
  colors[random16(LED_SEGMENT_COUNT)] = getColorPaletteRing(getPalette(), LED_SEGMENT_COUNT, 0, runner++, 255 * val / 100);
};
void Effect::starEffectHandle(uint8_t brightness)
{
  numOfZero = 0;
  for (uint16_t i = 0; i < LED_SEGMENT_COUNT; i++)
  {
    colors[i].fadeToBlackBy(16);
    if (operator==(colors[i], CRGB::Black))
      numOfZero++;
  }
  if (millis() - timer > speed)
  {
    if (numOfZero > LED_SEGMENT_COUNT / 3)
      colors[random16(LED_SEGMENT_COUNT)] = getColorPaletteRing(getPalette(), LED_SEGMENT_COUNT, 0, runner++, brightness);

    timer = millis();
  }
  SET_ALL_SEGMENT_COLORS(colors);
};