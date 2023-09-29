#include "effect.h"

EffectName stringToEffectName(String string)
{
  if (string == "EffectName_RunPaletteFace")
  {
    return EffectName_RunPaletteFace;
  }
  if (string == "EffectName_RunPaletteSegment")
  {
    return EffectName_RunPaletteSegment;
  }
  if (string == "EffectName_OverflowSegment")
  {
    return EffectName_OverflowSegment;
  }
  if (string == "EffectName_OverflowFace")
  {
    return EffectName_OverflowFace;
  }
};
String effectNameToString(EffectName effectName)
{
  if (effectName == EffectName_RunPaletteFace)
  {
    return "EffectName_RunPaletteFace";
  }
  if (effectName == EffectName_RunPaletteSegment)
  {
    return "EffectName_RunPaletteSegment";
  }
  if (effectName == EffectName_OverflowSegment)
  {
    return "EffectName_OverflowSegment";
  }
  if (effectName == EffectName_OverflowFace)
  {
    return "EffectName_OverflowFace";
  }
};

CRGBPalette16 stringToPalette(String string)
{
  if (string == "CloudColors_p")
    return CRGBPalette16(CloudColors_p);
  if (string == "LavaColors_p")
    return CRGBPalette16(LavaColors_p);
  if (string == "OceanColors_p")
    return CRGBPalette16(OceanColors_p);
  if (string == "ForestColors_p")
    return CRGBPalette16(ForestColors_p);
  if (string == "RainbowColors_p")
    return CRGBPalette16(RainbowColors_p);
  if (string == "RainbowStripeColors_p")
    return CRGBPalette16(RainbowStripeColors_p);
  if (string == "PartyColors_p")
    return CRGBPalette16(PartyColors_p);
  if (string == "HeatColors_p")
    return CRGBPalette16(HeatColors_p);
  return CRGBPalette16(Rainbow_gp);
};
String paletteToString(CRGBPalette16 palette)
{

  if (palette == CloudColors_p)
    return "CloudColors_p";
  if (palette == LavaColors_p)
    return "LavaColors_p";
  if (palette == OceanColors_p)
    return "OceanColors_p";
  if (palette == ForestColors_p)
    return "ForestColors_p";
  if (palette == RainbowColors_p)
    return "RainbowColors_p";
  if (palette == RainbowStripeColors_p)
    return "RainbowStripeColors_p";
  if (palette == PartyColors_p)
    return "PartyColors_p";
  if (palette == HeatColors_p)
    return "HeatColors_p";
  return "Rainbow_gp";
};