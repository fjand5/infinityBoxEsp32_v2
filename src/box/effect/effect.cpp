#include "effect.h"

CRGB Effect::getColorPaletteRing(CRGBPalette16 palette, uint16_t perimeter, uint16_t index, uint8_t brightness)
{
  index = index % perimeter;
  if (index >= perimeter)
  {
    index = perimeter - index;
  }
  return ColorFromPalette(palette, index * 256 / perimeter, brightness);
}
Effect::Effect(/* args */)
{
}

void Effect::setPalette(CRGBPalette16 palette)
{
  _newPalette = palette;
  _changePaletteTransition = 100;
};
CRGBPalette16 Effect::getPalette()
{
  return _newPalette;
};

void Effect::setEffectName(EffectName effectName)
{
  _lastEffectName = _effectName;
  _effectName = effectName;
  _changeEffectTransition = 255;
};
EffectName Effect::getEffectName()
{
  return _effectName;
};
void Effect::nextEffect()
{
  if ((int)getEffectName() + 1 == EffectName_Count)
    setEffectName((EffectName)0);
  else
    setEffectName(EffectName((int)getEffectName() + 1));
};
void Effect::nextPalette()
{
  if (getPalette() == CloudColors_p)
  {
    setPalette(LavaColors_p);
    return;
  }
  if (getPalette() == LavaColors_p)
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

void Effect::setRouter()
{
  ADD_SETTER_ROUTE(
      "/setEffectPalette", paletteToString(getPalette()), {
        setPalette(stringToPalette(value));
      },
      1000);
  ADD_SETTER_ROUTE(
      "/setNextEffectPalette", paletteToString(getPalette()), {
        nextPalette();
      },
      1000);
  ADD_SETTER_ROUTE(
      "/setEffectName", effectNameToString(getEffectName()), {
        setEffectName(stringToEffectName(value));
      },
      1000);
};

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

  default:
    break;
  }
};

void Effect::handle()
{
  /* testing */
  // static uint32_t timer__ = millis();
  // static uint32_t timer___ = millis();
  // if (millis() - timer__ > 10000)
  // {
  //   timer__ = millis();
  //   nextEffect();
  // }
  // if (millis() - timer___ > 15000)
  // {
  //   timer___ = millis();
  //   nextPalette();
  // }
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

    default:
      break;
    }
    _changeEffectTransition -= 1;
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

  default:
    break;
  }
};

Effect::~Effect()
{
}