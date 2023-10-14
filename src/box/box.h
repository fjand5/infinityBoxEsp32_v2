#define PREF_BOX_NAME "__box"
#include <FastLED.h>

#include "env.h"
#include "web/web.h"
#include "microphone.h"
#include "effect/effect.h"
#include "pref/pref.h"
extern Microphone microphone;

class Box : public Effect, private Pref
{
private:
  /* data */

  bool _onMicrophone;
  uint8_t _brightness;

  bool _stop = false;
  bool _powerOn = true;

  ICRGB _pixels[LED_COUNT];

  static void handle(void *param);
  void show();

  void setRouter();

public:
  Box();
  void begin();

  virtual void setPalette(CRGBPalette16 palette);
  virtual CRGBPalette16 getPalette();

  virtual void setEffectName(EffectName EffectName);
  virtual EffectName getEffectName();
  
  void setAutoChangeMode(bool enable);
  bool getAutoChangeMode();

  void setTimeAutoChangeMode(uint32_t time);
  uint32_t getTimeAutoChangeMode();

  virtual void setStop(bool stop);
  bool getStop();

  void setPowerOn(bool powerOn);
  bool getPowerOn();

  void setBrightness(uint8_t brightness);
  uint8_t getBrightness();

  void setOnMicrophone(bool onMicrophone);
  bool getOnMicrophone();

  virtual ICRGB *getPixels();

  ~Box();
};
extern Box box;
