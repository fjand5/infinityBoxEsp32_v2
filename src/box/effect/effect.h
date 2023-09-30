#define PREF_BOX_NAME "__box"
#include <FastLED.h>
#include "../accessPixels.h"
#include "web/web.h"
#include "button/button.h"
typedef enum
{
  EffectName_RunPaletteFace,
  EffectName_RunPaletteSegment,
  EffectName_OverflowSegment,
  EffectName_OverflowFace,
  EffectName_Count,
} EffectName;
EffectName stringToEffectName(String string);
String effectNameToString(EffectName effectName);
CRGBPalette16 stringToPalette(String string);
String paletteToString(CRGBPalette16 palette);

class Effect : public AccessPixels
{
private:
  CRGBPalette16 _palette = CRGBPalette16(ForestColors_p);
  CRGBPalette16 _newPalette = CRGBPalette16(ForestColors_p);
  int8_t _changePaletteTransition = 0;

  EffectName _effectName = EffectName_RunPaletteSegment;
  EffectName _lastEffectName = EffectName_OverflowFace;
  uint8_t _changeEffectTransition = 0;

  CRGB getColorPaletteRing(CRGBPalette16 palette, uint16_t perimeter, uint16_t index, uint8_t brightness = 255);

protected:
  bool _autoChangeMode;

public:
  Effect(/* args */);

  void nextEffect();
  void nextPalette();
  // void setRouter();

  // virtual bool getOnMicrophone() = 0;
  // virtual void saveEffect()=0;


  void setPalette(CRGBPalette16 palette);
  CRGBPalette16 getPalette();

  void setEffectName(EffectName EffectName);
  EffectName getEffectName();

  void handle();
  void onBeat(double val, double freq);
  /* Effects */
  void runPaletteFaceEffectOnBeat(double val, double freq);
  void runPaletteFaceEffectHandle(uint8_t brightness);

  void overflowSegmentEffectOnBeat(double val, double freq);
  void overflowSegmentEffectHandle(uint8_t brightness);

  void overflowFaceEffectOnBeat(double val, double freq);
  void overflowFaceEffectHandle(uint8_t brightness);

  void runPaletteSegmentEffectOnBeat(double val, double freq);
  void runPaletteSegmentEffectHandle(uint8_t brightness);
  ~Effect();
};
