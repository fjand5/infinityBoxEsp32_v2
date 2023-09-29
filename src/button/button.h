#pragma once
#define PREF_BUTTON_NAME "__button"
#include "env.h"
#include <Arduino.h>
#include <functional>
typedef std::function<void(void)> OnClick;
typedef std::function<void(uint32_t)> OnLongClick;
typedef enum
{
  ButtonLedMode_Blink,
  ButtonLedMode_FastBlink,
  ButtonLedMode_Fade,
  ButtonLedMode_FastFade,
} ButtonLedMode;
class Button
{
private:
  /* data */
  static void handleButton(void *param);
  static void handleLed(void *param);


  OnClick _onClick = nullptr;
  OnLongClick _onLongClick = nullptr;
  OnLongClick _onLongLongClick = nullptr;

public:
  Button(/* args */);
  void setOnClick(OnClick onclick);
  void setOnLongClick(OnLongClick onLongClick);
  void setOnLongLongClick(OnLongClick onLongLongClick);
  void begin();

  void setButtonLedMode(ButtonLedMode buttonLedMode);
  ButtonLedMode getButtonLedMode();
  ~Button();
};
extern Button button;
