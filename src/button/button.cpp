#include "button.h"
Button button;
Button::Button(/* args */)
{
}
void Button::setOnClick(OnClick onclick)
{
  _onClick = onclick;
};

void Button::handle(void *param)
{
  static bool lastState = digitalRead(BUTTON_PIN);
  static bool currentState = digitalRead(BUTTON_PIN);
  while (1)
  {
    currentState = digitalRead(BUTTON_PIN);
    if (lastState == HIGH && currentState == LOW && button._onClick)
    {
      button._onClick();
    }
    lastState = currentState;
    delay(20);
  }
};

void Button::begin(/* args */)
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  xTaskCreatePinnedToCore(
      handle,
      PREF_BUTTON_NAME,
      1000,
      NULL,
      99,
      NULL,
      1);
}

Button::~Button()
{
}