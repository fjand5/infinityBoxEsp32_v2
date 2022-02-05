#include "control_button.h"
ControlButton controlButton(BUTTON_PIN);

ControlButton::ControlButton(uint8_t pin) : EasyButton(pin)
{
}

void ControlButton::resetFactory()
{
    SPIFFS.format();
    delay(1000);
    ESP.restart();
}
void ControlButton::setClickEvent(ClickEvent cbClickEvent)
{
    clickEvent = cbClickEvent;
};
void ControlButton::begin()
{

    begin();
    // onPressedFor(PRESS_TIME, onPressed);
    // onSequence(2, DOUBLE_CLICK_DURATION, doubleClick);

    ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
    ledcAttachPin(LED_BUTTON_PIN, LEDC_CHANNEL_0);

    xTaskCreatePinnedToCore(
        [](void *param)
        {
            class ControlButton_Private : public ControlButton
            {
            private:
                /* data */
            public:
                ControlButton_Private(/* args */);
            };
            ControlButton_Private *_controlButton = (ControlButton_Private *)param;

            static uint32_t lastClickTime = 0;
            int countToFactoryReset = 0;
            int brightness = 0;  // how bright the LED is
            int fadeAmount = 10; // how many points to fade the LED by

            _controlButton->onPressed([]()
                                      { lastClickTime = millis(); });
            while (1)
            {
                vTaskDelay(50 / portTICK_PERIOD_MS);
                _controlButton->read();

                if (lastClickTime != 0 && millis() - lastClickTime > DOUBLE_CLICK_DURATION)
                {
                    lastClickTime = 0;
                    if (_controlButton->clickEvent != NULL)
                        _controlButton->clickEvent();
                }
                brightness = brightness + fadeAmount;
                if (brightness <= 0 || brightness >= 250)
                {
                    fadeAmount = -fadeAmount;
                }
                ledcWrite(LEDC_CHANNEL_0, brightness);
            }
        },                     /* Task function. */
        "controlButtonHandle", /* name of task. */
        10000,                 /* Stack size of task */
        (void *)this,          /* parameter of the task */
        0,                     /* priority of the task */
        NULL,                  /* Task handle to keep track of created task */
        BUTTON_CORE_CPU);      /* pin task to core 0 */
};
ControlButton::~ControlButton()
{
}
