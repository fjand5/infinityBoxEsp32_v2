#include "effect.h"
static uint16_t runner = 0;
static uint16_t width = 6;
static uint32_t timer = 0;
static uint32_t speed = 100;
static ICRGB colors[LED_FACE_COUNT] = {ICRGB(CRGB::Black, EffectName_ShowPaletteFace)}; // box.getPixels() + box.getSegmentPosition(sn);

void Effect::showPaletteFaceEffectOnBeat(double val, double freq)
{
  if(val<10)return;
  speed = (100 - val)/2;
  runner++;
  timer = 0;
};
void Effect::showPaletteFaceEffectHandle(uint8_t brightness)
{

  for (uint16_t i = 0; i < LED_FACE_COUNT; i++)
  {

    colors[i] = getColorPaletteRing(getPalette(), 3, 3, i + runner, brightness);
  }

  if (speed < 100)
    speed++;
  if (millis() - timer > speed)
  {

    runner++;
    timer = millis();
  }
  SET_ALL_FACE_COLORS(colors);
};