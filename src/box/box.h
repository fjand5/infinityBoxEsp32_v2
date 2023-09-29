#define PREF_BOX_NAME "__box"
#include <FastLED.h>

#include "env.h"
#include "web/web.h"
// #include "showDriver.h"
// #include "accessPixels.h"
#include "microphone.h"
#include "effect/effect.h"
extern Microphone microphone;

class Box : public Effect
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

  void setBrightness(uint8_t brightness);
  uint8_t getBrightness();

  void setOnMicrophone(bool onMicrophone);
  virtual bool getOnMicrophone();
  
  virtual ICRGB *getPixels();
  ~Box();
};
extern Box box;
