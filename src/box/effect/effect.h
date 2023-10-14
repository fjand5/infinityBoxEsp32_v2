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
  EffectName_VUMeterSegment,
  EffectName_ShowPaletteFace,
  EffectName_VUMeterHalfSegment,
  EffectName_StarSegment,
  EffectName_Count,
} EffectName;
EffectName stringToEffectName(String string);
String effectNameToString(EffectName effectName);
CRGBPalette16 stringToPalette(String string);
String paletteToString(CRGBPalette16 palette);

class Effect : public AccessPixels
{
private:

protected:
  CRGBPalette16 _palette = CRGBPalette16(ForestColors_p);
  CRGBPalette16 _newPalette = CRGBPalette16(ForestColors_p);
  int8_t _changePaletteTransition = 0;

  EffectName _effectName = EffectName_RunPaletteSegment;
  EffectName _lastEffectName = EffectName_OverflowFace;
  uint8_t _changeEffectTransition = 0;

  bool _autoChangeMode;

  uint32_t _timeAutoMode = 1000;

public:
  Effect(/* args */);

  CRGB getColorPaletteRing(CRGBPalette16 palette, uint16_t perimeter, uint16_t padding, uint16_t index, uint8_t brightness = 255);

  void nextEffect();
  void previousEffect();
  void nextPalette();

  virtual void setPalette(CRGBPalette16 palette) = 0;
  virtual CRGBPalette16 getPalette() = 0;

  virtual void setEffectName(EffectName EffectName) = 0;
  virtual EffectName getEffectName() = 0;

  virtual void setStop(bool stop) = 0;

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

  void vUMeterSegmentEffectOnBeat(double val, double freq);
  void vUMeterSegmentEffectHandle(uint8_t brightness);

  void showPaletteFaceEffectOnBeat(double val, double freq);
  void showPaletteFaceEffectHandle(uint8_t brightness);

  void vUMeterHalfSegmentEffectOnBeat(double val, double freq);
  void vUMeterHalfSegmentEffectHandle(uint8_t brightness);

  void starEffectOnBeat(double val, double freq);
  void starEffectHandle(uint8_t brightness);
  ~Effect();
};
