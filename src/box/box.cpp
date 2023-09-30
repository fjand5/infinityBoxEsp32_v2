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
    if (box._onMicrophone)
    {
      microphone.handleMicrophone(
          [](void *param, double val, double freq)
          {
            box.Effect::onBeat(val, freq);
          },
          nullptr);
    }
    box.Effect::handle();
    box.show();
  }
};

void Box::setRouter()
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
  ADD_SETTER_ROUTE(
      "/setAutoMode", getAutoChangeMode(), {
        setAutoChangeMode(value == "true");
      },
      1000);

  ADD_SETTER_ROUTE(
      "/setBoxBrightness",
      getBrightness(), {
        setBrightness(value.toInt());
      },
      1000)
  ADD_SETTER_ROUTE(
      "/setOnMicrophone",
      getOnMicrophone(), {
        setOnMicrophone(value == "true");
      },
      1000)
  ADD_GETTER_ROUTE(
      "/getBox", {
        obj["autoMode"] = getAutoChangeMode();
        obj["onMicrophone"] = getOnMicrophone();
        obj["brightness"] = getBrightness();
      },
      1000);
};

void Box::begin()
{
  Pref::begin(PREF_BOX_NAME);
  init();
  FastLED.addLeds<NEOPIXEL, LED_PIN>(new CRGB[LED_COUNT], LED_COUNT);

  // Setup segment

  microphone.begin();
  setRouter();

  setFaceData(FaceName_Top, {16 * LED_SEGMENT_COUNT, true});
  setFaceData(FaceName_Bottom, {4 * LED_SEGMENT_COUNT, false});
  setFaceData(FaceName_Left, {20 * LED_SEGMENT_COUNT, true});
  setFaceData(FaceName_Right, {8 * LED_SEGMENT_COUNT, false});
  setFaceData(FaceName_Front, {12 * LED_SEGMENT_COUNT, true});
  setFaceData(FaceName_Back, {0 * LED_SEGMENT_COUNT, false});

  setBrightness(_preferences.getUChar("brightness", 255));
  setAutoChangeMode(_preferences.getBool("autoMode", false));
  setOnMicrophone(_preferences.getBool("onMicrophone", false));
  xTaskCreatePinnedToCore(
      handle,
      PREF_BOX_NAME,
      10000,
      nullptr,
      99,
      NULL,
      1);
};

void Box::setAutoChangeMode(bool enable)
{
  _autoChangeMode = enable;

  if (_autoChangeMode)
  {
    if (getOnMicrophone())
      button.setButtonLedMode(ButtonLedMode_FastFade);
    else
      button.setButtonLedMode(ButtonLedMode_FastBlink);
  }
  else
  {
    if (getOnMicrophone())
      button.setButtonLedMode(ButtonLedMode_Fade);
    else
      button.setButtonLedMode(ButtonLedMode_Blink);
  }

  _preferences.putBool("autoMode", getAutoChangeMode());
};
bool Box::getAutoChangeMode()
{
  return _autoChangeMode;
};
void Box::setBrightness(uint8_t brightness)
{
  _brightness = brightness;

  _preferences.putUChar("brightness", getBrightness());
};
uint8_t Box::getBrightness()
{
  return _brightness;
};

void Box::setOnMicrophone(bool onMicrophone)
{
  _onMicrophone = onMicrophone;

  if (_onMicrophone)
  {

    if (getAutoChangeMode())
    {
      button.setButtonLedMode(ButtonLedMode_FastFade);
    }
    else
    {
      button.setButtonLedMode(ButtonLedMode_Fade);
    }
  }
  else
  {
    if (getAutoChangeMode())
    {
      button.setButtonLedMode(ButtonLedMode_FastBlink);
    }
    else
    {
      button.setButtonLedMode(ButtonLedMode_Blink);
    }
  }
  _preferences.putBool("onMicrophone", getOnMicrophone());
};
bool Box::getOnMicrophone()
{
  return _onMicrophone;
};
ICRGB *Box::getPixels()
{
  return _pixels;
};
Box::~Box()
{
}
