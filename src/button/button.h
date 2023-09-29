#pragma once
#define PREF_BUTTON_NAME "__button"
#include "env.h"
#include <Arduino.h>
#include <functional>
typedef std::function<void(void)> OnClick;

class Button
{
private:
  /* data */
  static void handle(void *param);

  OnClick _onClick = nullptr;

  
public:
  Button(/* args */);
  void setOnClick(OnClick onclick);
  void begin();
  ~Button();
};
extern Button button;
