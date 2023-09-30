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

  ICRGB _pixels[LED_COUNT];

  static void handle(void *param);
  void show();

  void setRouter();

public:
  Box();
  void begin();

  void setAutoChangeMode(bool enable);
  bool getAutoChangeMode();

  void setBrightness(uint8_t brightness);
  uint8_t getBrightness();

  void setOnMicrophone(bool onMicrophone);
  bool getOnMicrophone();

  virtual ICRGB *getPixels();

  ~Box();
};
extern Box box;
