#include "effect.h"
static uint16_t runner = 0;
static uint16_t width = 0;
static uint32_t timer = 0;
static uint32_t speed = 25;
static ICRGB colors[LED_HALFFACE_COUNT + 1] = {ICRGB(CRGB::Black, EffectName_OverflowFace)}; // Thêm 1 cho việc dịch phải.

void Effect::overflowFaceEffectOnBeat(double val, double freq)
{
  if (val < 10)
    return;
  if (operator!=(colors[0], CRGB::Black))
  {
    for (int i = LED_HALFFACE_COUNT - 1; i >= 0; i--)
    {
      colors[i + 1] = colors[i];
    }
  }
  colors[0] = ColorFromPalette(getPalette(), freq * 256 / 100);
  colors[0].i = EffectName_OverflowFace;
};
void Effect::overflowFaceEffectHandle(uint8_t brightness)
{
  int numOfBlack = 0;

  if (millis() - timer > speed)
  {

    runner++;
    // if (runner >= LED_HALFFACE_COUNT)
    //   runner = 0;
    timer = millis();
    for (int i = 0; i < LED_HALFFACE_COUNT; i++)
    {
      if (colors[i].i == -EffectName_OverflowFace || operator==(colors[i], CRGB::Black))
      {
        numOfBlack++;
      }
    }
    if (numOfBlack == LED_HALFFACE_COUNT)
    {
      speed = 50;
      static int16_t runLoop = 0;
      static int16_t runLoopSig = 1;
      runLoop += runLoopSig;
      if (runLoop <= 0)
      {
        runLoopSig = 1;
      }
      if (runLoop >= LED_HALFFACE_COUNT - 1)
      {
        runLoopSig = -1;
      }
      for (int i = 0; i < LED_HALFFACE_COUNT; i++)
      {
        if (i == runLoop)
        {
          colors[i] = getColorPaletteRing(getPalette(), LED_HALFFACE_COUNT,0, runner, brightness);
          colors[i].i = -EffectName_OverflowFace;
        }
        else
        {
          colors[i] = CRGB::Black;
          colors[i].i = EffectName_OverflowFace;
        }
      }
    }
    else
    {
      for (int i = LED_HALFFACE_COUNT - 1; i >= 0; i--)
      {
        colors[i + 1] = colors[i];
      }
      speed = 25;
      // SET_ALL_HALFFace_COLORS phải chạy trước để tránh tất cả led đều tắt.
      SET_ALL_HALFFACE_COLORS(colors);
      colors[0] = 0;
      colors[0].i = EffectName_OverflowFace;

      return;
    }
  }
  SET_ALL_HALFFACE_COLORS(colors);
};