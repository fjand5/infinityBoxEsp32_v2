#include "button.h"
Button button;

static bool currentState = digitalRead(BUTTON_PIN);
static uint32_t lowButtonTicks = 0;
static int16_t ledBrightness = 0;
static int8_t dirBrightness = 1;
static ButtonLedMode _buttonLedMode = ButtonLedMode_FastFade;
static TaskHandle_t xLedHandle;

Button::Button(/* args */)
{
}
void Button::setOnClick(OnClick onclick)
{
  _onClick = onclick;
};
void Button::setOnLongClick(OnLongClick onLongClick)
{
  _onLongClick = onLongClick;
};
void Button::setOnLongLongClick(OnLongClick onLongLongClick)
{
  _onLongLongClick = onLongLongClick;
};
void Button::handleLed(void *param)
{
  static uint32_t blinkTimer = millis();
  while (1)
  {
    switch (_buttonLedMode)
    {
    case ButtonLedMode_Blink:
      if (millis() - blinkTimer > 750)
      {
        blinkTimer = millis();
        if (ledBrightness == 255)
        {
          ledBrightness = 0;
        }
        else
        {
          ledBrightness = 255;
        }
      }
      break;
    case ButtonLedMode_FastBlink:
      if (millis() - blinkTimer > 150)
      {
        blinkTimer = millis();
        if (ledBrightness == 255)
        {
          ledBrightness = 0;
        }
        else
        {
          ledBrightness = 255;
        }
      }
      break;
    case ButtonLedMode_Fade:
      if (ledBrightness >= 255)
      {
        dirBrightness = -3;
      }
      if (ledBrightness <= 0)
      {
        dirBrightness = 3;
      }
      ledBrightness += dirBrightness;

      break;
    case ButtonLedMode_FastFade:
      if (ledBrightness >= 255)
      {
        dirBrightness = -15;
      }
      if (ledBrightness <= 0)
      {
        dirBrightness = 15;
      }
      ledBrightness += dirBrightness;

      break;

    default:
      break;
    }

    ledcWrite(LEDC_CHANNEL_0, ledBrightness);
    delay(20);
  }
};

void Button::handleButton(void *param)
{
  while (1)
  {
    delay(BUTTON_TICK_LOOP);
    currentState = digitalRead(BUTTON_PIN);
    if (currentState == LOW)
      lowButtonTicks++;
    if (lowButtonTicks > 0)
    {
      // Nếu vẫn đang giữ nút thì tắt led
      vTaskSuspend(xLedHandle);
      ledcWrite(LEDC_CHANNEL_0, 0);
    }
    if (lowButtonTicks > BUTTON_LONG_CLICK_TIME / BUTTON_TICK_LOOP && lowButtonTicks < BUTTON_LONG_LONG_CLICK_TIME / BUTTON_TICK_LOOP)
    {
      // Nếu vẫn đang giữ nút đến khi đủ thời gian longclick thì bật lại led một nữa
      ledcWrite(LEDC_CHANNEL_0, 64);
    }
    if (lowButtonTicks >= BUTTON_LONG_LONG_CLICK_TIME / BUTTON_TICK_LOOP)
    {
      // Nếu vẫn đang giữ nút đến khi đủ thời gian longlongclick thì bật lại led tối đa
      ledcWrite(LEDC_CHANNEL_0, 255);
    }
    if (currentState == HIGH)
    {
      if (lowButtonTicks >= BUTTON_LONG_LONG_CLICK_TIME / BUTTON_TICK_LOOP)
      {
        if (button._onLongLongClick)
          button._onLongLongClick(lowButtonTicks);
        lowButtonTicks = 0;
        ledcWrite(LEDC_CHANNEL_0, 255);
        delay(250);
        ledcWrite(LEDC_CHANNEL_0, 0);
        delay(250);
        ledcWrite(LEDC_CHANNEL_0, 255);
        delay(250);
        ledcWrite(LEDC_CHANNEL_0, 0);
        delay(250);
      }
      if (lowButtonTicks >= BUTTON_LONG_CLICK_TIME / BUTTON_TICK_LOOP && lowButtonTicks < BUTTON_LONG_LONG_CLICK_TIME / BUTTON_TICK_LOOP)
      {
        if (button._onLongClick)
          button._onLongClick(lowButtonTicks);
        lowButtonTicks = 0;
        ledcWrite(LEDC_CHANNEL_0, 255);
        delay(250);
        ledcWrite(LEDC_CHANNEL_0, 0);
        delay(250);
        ledcWrite(LEDC_CHANNEL_0, 255);
        delay(250);
        ledcWrite(LEDC_CHANNEL_0, 0);
        delay(250);
      }
      if (lowButtonTicks >= BUTTON_CLICK_TIME / BUTTON_TICK_LOOP && lowButtonTicks < BUTTON_LONG_CLICK_TIME / BUTTON_TICK_LOOP)
      {
        if (button._onClick)
          button._onClick();
        lowButtonTicks = 0;
        ledcWrite(LEDC_CHANNEL_0, 255);
        delay(150);
        ledcWrite(LEDC_CHANNEL_0, 0);
        delay(150);
        ledcWrite(LEDC_CHANNEL_0, 255);
        delay(150);
        ledcWrite(LEDC_CHANNEL_0, 0);
        delay(150);
      }
      vTaskResume(xLedHandle);
    }
  }
};
void Button::setButtonLedMode(ButtonLedMode buttonLedMode)
{
  _buttonLedMode = buttonLedMode;
  ledBrightness = 0;
};
ButtonLedMode Button::getButtonLedMode()
{
  return _buttonLedMode;
};

void Button::begin(/* args */)
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
  ledcAttachPin(LED_BUTTON_PIN, LEDC_CHANNEL_0);
  xTaskCreatePinnedToCore(
      handleButton,
      PREF_BUTTON_NAME "-btn",
      1000,
      NULL,
      99,
      NULL,
      1);
  xTaskCreatePinnedToCore(
      handleLed,
      PREF_BUTTON_NAME "-led",
      1000,
      NULL,
      99,
      &xLedHandle,
      1);
}

Button::~Button()
{
}