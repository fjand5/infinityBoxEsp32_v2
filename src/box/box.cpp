#include "box.h"
Box box;
Box::Box()
{
}
void Box::show()
{
  for (size_t i = 0; i < FastLED.size(); i++)
  {
    FastLED.leds()[i] = _pixels[i];
    _pixels[i] = 0;
  }

  FastLED.show(getBrightness());
};

void Box::handle(void *param)
{

  while (1)
  {
    microphone.handleMicrophone(
        [](void *param, double val, double freq)
        {

          box.Effect::onBeat(val, freq);
        },
        nullptr);
    box.Effect::handle();
    box.show();
  }
};

void Box::setRouter()
{
  Effect::setRouter();
  ADD_SETTER_ROUTE(
      "/setBoxBrightness",
      getBrightness(), {
        setBrightness(value.toInt());
      },
      1000)
};

void Box::begin()
{
  init();
  FastLED.addLeds<NEOPIXEL, LED_PIN>(new CRGB[LED_COUNT], LED_COUNT);

  // Setup segment
  setFaceData(FaceName_Top, {16 * LED_SEGMENT_COUNT, true});
  setFaceData(FaceName_Bottom, {4 * LED_SEGMENT_COUNT, false});
  setFaceData(FaceName_Left, {20 * LED_SEGMENT_COUNT, true});
  setFaceData(FaceName_Right, {8 * LED_SEGMENT_COUNT, false});
  setFaceData(FaceName_Front, {12 * LED_SEGMENT_COUNT, true});
  setFaceData(FaceName_Back, {0 * LED_SEGMENT_COUNT, false});

  // Setup brightness
  _brightness = 255;
  microphone.begin();
  setRouter();
  xTaskCreatePinnedToCore(
      handle,
      PREF_BOX_NAME,
      10000,
      nullptr,
      99,
      NULL,
      1);
};

void Box::setBrightness(uint8_t brightness)
{
  _brightness = brightness;
};
uint8_t Box::getBrightness()
{
  return _brightness;
};
ICRGB *Box::getPixels()
{
  return _pixels;
};

Box::~Box()
{
}
