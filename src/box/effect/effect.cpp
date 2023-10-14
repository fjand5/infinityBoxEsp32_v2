#include "effect.h"

CRGB Effect::getColorPaletteRing(CRGBPalette16 palette, uint16_t perimeter, uint16_t padding, uint16_t index, uint8_t brightness)
{
  uint16_t _perimeter = perimeter + padding;
  index = index % _perimeter;
  if (index >= _perimeter)
  {
    index = _perimeter - index;
  }
  if (index > perimeter)
    return CRGB::Black;
  if (index == perimeter)
    return mixColor(ColorFromPalette(palette, index * 256 / _perimeter, brightness), CRGB::Black, 25);
  return ColorFromPalette(palette, index * 256 / _perimeter, brightness);
}
Effect::Effect(/* args */)
{
}
void Effect::nextEffect()
{
  if ((int)getEffectName() + 1 == EffectName_Count)
    setEffectName((EffectName)0);
  else
    setEffectName(EffectName((int)getEffectName() + 1));

  setStop(false);
};
void Effect::previousEffect()
{
  if ((int)getEffectName() - 1 == 0)
    setEffectName((EffectName)(EffectName_Count - 1));
  else
    setEffectName(EffectName((int)getEffectName() - 1));
  setStop(false);
};
void Effect::nextPalette()
{
  // if (getPalette() == CloudColors_p)
  // {
  //   setPalette(LavaColors_p);
  //   return;
  // }
  if (getPalette() == CloudColors_p)
  {
    setPalette(OceanColors_p);
    return;
  }
  if (getPalette() == OceanColors_p)
  {
    setPalette(ForestColors_p);
    return;
  }
  if (getPalette() == ForestColors_p)
  {
    setPalette(RainbowColors_p);
    return;
  }
  if (getPalette() == RainbowColors_p)
  {
    setPalette(RainbowStripeColors_p);
    return;
  }
  if (getPalette() == RainbowStripeColors_p)
  {
    setPalette(PartyColors_p);
    return;
  }
  if (getPalette() == PartyColors_p)
  {
    setPalette(HeatColors_p);
    return;
  }
  if (getPalette() == HeatColors_p)
  {
    setPalette(CloudColors_p);
    return;
  }
};

// void Effect::setRouter()
// {

// };

void Effect::onBeat(double val, double freq)
{

  switch (_effectName)
  {
  case EffectName_RunPaletteFace:
    runPaletteFaceEffectOnBeat(val, freq);
    break;
  case EffectName_RunPaletteSegment:
    runPaletteSegmentEffectOnBeat(val, freq);
    break;
  case EffectName_OverflowSegment:
    overflowSegmentEffectOnBeat(val, freq);
    break;
  case EffectName_OverflowFace:
    overflowFaceEffectOnBeat(val, freq);
    break;
  case EffectName_VUMeterSegment:
    vUMeterSegmentEffectOnBeat(val, freq);
    break;
  case EffectName_ShowPaletteFace:
    showPaletteFaceEffectOnBeat(val, freq);
    break;
  case EffectName_VUMeterHalfSegment:
    vUMeterHalfSegmentEffectOnBeat(val, freq);
    break;
  case EffectName_StarSegment:
    starEffectOnBeat(val, freq);
    break;

  default:
    break;
  }
};

void Effect::handle()
{
  /* testing */
  if (_autoChangeMode)
  {
    static uint32_t colorTimer = millis();
    static uint32_t effecttimer = millis();
    if (millis() - effecttimer > _timeAutoMode)
    {
      effecttimer = millis();
      nextEffect();
    }
    if (millis() - colorTimer > _timeAutoMode / 2)
    {
      colorTimer = millis();
      nextPalette();
    }
  }
  if (_changePaletteTransition > 0)
  {
    for (uint8_t i = 0; i < 16; i++)
    {
      _palette[i] = mixColor(_palette[i], _newPalette[i], _changePaletteTransition);
    }
    _changePaletteTransition -= 1;
  }
  if (_changeEffectTransition > 0)
  {
    switch (_lastEffectName)
    {
    case EffectName_RunPaletteFace:
      runPaletteFaceEffectHandle(_changeEffectTransition);
      break;
    case EffectName_RunPaletteSegment:
      runPaletteSegmentEffectHandle(_changeEffectTransition);
      break;
    case EffectName_OverflowSegment:
      overflowSegmentEffectHandle(_changeEffectTransition);
      break;
    case EffectName_OverflowFace:
      overflowFaceEffectHandle(_changeEffectTransition);
      break;
    case EffectName_VUMeterSegment:
      vUMeterSegmentEffectHandle(_changeEffectTransition);
      break;
    case EffectName_ShowPaletteFace:
      showPaletteFaceEffectHandle(_changeEffectTransition);
      break;
    case EffectName_VUMeterHalfSegment:
      vUMeterHalfSegmentEffectHandle(_changeEffectTransition);
      break;
    case EffectName_StarSegment:
      starEffectHandle(_changeEffectTransition);
      break;

    default:
      break;
    }
    // Phải trừ một lượng chia hết cho 255
    _changeEffectTransition -= 5;
  }
  switch (_effectName)
  {
  case EffectName_RunPaletteFace:
    runPaletteFaceEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_RunPaletteSegment:
    runPaletteSegmentEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_OverflowSegment:
    overflowSegmentEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_OverflowFace:
    overflowFaceEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_VUMeterSegment:
    vUMeterSegmentEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_ShowPaletteFace:
    showPaletteFaceEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_VUMeterHalfSegment:
    vUMeterHalfSegmentEffectHandle(255 - _changeEffectTransition);
    break;
  case EffectName_StarSegment:
    starEffectHandle(255 - _changeEffectTransition);
    break;

  default:
    break;
  }
};

Effect::~Effect()
{
}