// #include "control_button.h"
// ControlButton controlButton(BUTTON_PIN);

// ControlButton::ControlButton(uint8_t pin) : EasyButton(pin)
// {
// }

// void ControlButton::resetFactory()
// {
//     SPIFFS.format();
//     delay(1000);
//     ESP.restart();
// }
// void ControlButton_Handle::buttonHandle()
// {

//     static uint32_t lastClickTime = 0;
//     static DoubleClickEvent _doubleClickEvent = doubleClickEvent;
//     onPressed(
//         []()
//         {
//             lastClickTime = millis();
//         });

//     onPressedFor(PRESS_TIME,
//                  []()
//                  {
//                      log_w("Format and restart");
//                      resetFactory();
//                  });
//     onSequence(2, DOUBLE_CLICK_DURATION,
//                []()
//                {
//                    log_w("On double click");
//                    lastClickTime = 0;
//                    if (_doubleClickEvent != NULL)
//                    {
//                        _doubleClickEvent();
//                    }
//                });
//     while (1)
//     {
//         vTaskDelay(50 / portTICK_PERIOD_MS);
//         read();
//         if (lastClickTime != 0 && millis() - lastClickTime > DOUBLE_CLICK_DURATION)
//         {
//             lastClickTime = 0;
//             log_w("On click");
//             if (clickEvent != NULL)
//             {
//                 clickEvent();
//             }
//         }
//     }
// }
// void ControlButton_Handle::ledHandle()
// {

//     int brightness = 0;                    // how bright the LED is
//     int fadeAmountFast = FADE_FAST_FACTOR; // how many points to fade the LED by
//     int fadeAmountSlow = FADE_SLOW_FACTOR; // how many points to fade the LED by
//     while (1)
//     {
//         vTaskDelay(50 / portTICK_PERIOD_MS);
//         switch (ledMode)
//         {
//         case LedMode_Blink:
//         {
//             static auto lastTimeBlink = millis();
//             if (millis() - lastTimeBlink > BLINK_CYCLE)
//             {
//                 lastTimeBlink = millis();
//                 if (brightness == 0)
//                     brightness = 255;
//                 else
//                     brightness = 0;
//             }
//         }
//         break;
//         case LedMode_Off:
//         {
//             brightness = 0;
//         }
//         break;
//         case LedMode_On:
//         {
//             brightness = 255;
//         }
//         break;
//         case LedMode_FadeFast:
//         {
//             if (brightness <= FADE_FAST_FACTOR)
//             {
//                 fadeAmountFast = FADE_FAST_FACTOR;
//             }
//             else if (brightness >= 255 - FADE_FAST_FACTOR)
//             {
//                 fadeAmountFast = -FADE_FAST_FACTOR;
//             }
//             brightness = brightness + fadeAmountFast;
//         }
//         break;
//         case LedMode_FadeSlow:
//         {
//             if (brightness <= FADE_SLOW_FACTOR)
//             {
//                 fadeAmountSlow= FADE_SLOW_FACTOR;
//             }
//             else if (brightness >= 255 - FADE_SLOW_FACTOR)
//             {
//                 fadeAmountSlow= -FADE_SLOW_FACTOR;
//             }
//             brightness = brightness + fadeAmountSlow;
//         }
//         break;
//         }
//         ledcWrite(LEDC_CHANNEL_0, brightness);
//     }
// }
// void ControlButton::setLedMode(LedMode mode)
// {
//     ledMode = mode;
// };

// void ControlButton::setClickEvent(ClickEvent cbClickEvent)
// {
//     clickEvent = cbClickEvent;
// };

// void ControlButton::setDoubleClickEvent(DoubleClickEvent cdDoubleClickEvent)
// {
//     doubleClickEvent = cdDoubleClickEvent;
// };
// void ControlButton::begin()
// {

//     EasyButton::begin();

//     ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
//     ledcAttachPin(LED_BUTTON_PIN, LEDC_CHANNEL_0);
//     xTaskCreatePinnedToCore(
//         [](void *param)
//         {
//             ControlButton_Handle *_controlButton = (ControlButton_Handle *)param;
//             _controlButton->buttonHandle();
//         },                /* Task function. */
//         "buttonHandle",   /* name of task. */
//         2048,             /* Stack size of task */
//         (void *)this,     /* parameter of the task */
//         0,                /* priority of the task */
//         NULL,             /* Task handle to keep track of created task */
//         BUTTON_CORE_CPU); /* pin task to core 0 */

//     xTaskCreatePinnedToCore(
//         [](void *param)
//         {
//             ControlButton_Handle *_controlButton = (ControlButton_Handle *)param;
//             _controlButton->ledHandle();
//         },                /* Task function. */
//         "ledHandle",      /* name of task. */
//         2048,             /* Stack size of task */
//         (void *)this,     /* parameter of the task */
//         0,                /* priority of the task */
//         NULL,             /* Task handle to keep track of created task */
//         BUTTON_CORE_CPU); /* pin task to core 0 */
// };
// ControlButton::~ControlButton()
// {
// }
