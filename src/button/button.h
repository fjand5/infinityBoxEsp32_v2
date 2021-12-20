#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000
#include "button_env.h"
#include "voca_core.h"
#include "box/box_controler.h"

#include <EasyButton.h>
#include <Arduino.h>
#include <LITTLEFS.h>

#define DOUBLE_CLICK_DURATION 300
EasyButton button(BUTTON_PIN);
uint32_t lastClickTime = 0;

int countToFactoryReset = 0;
void resetFactory()
{
    LITTLEFS.format();
    delay(1000);
    ESP.restart();
}
void onClick()
{
    log_d(" onClick");
    box_nextMode();
    // if (getValue("on_off_tgl") != "true")
    // {
    //     setValue("on_off_tgl", "true");
    //     onBox();
    // }
    // else
    // {
    // }
}
void onPressed()
{
    log_d(" onPressed");
}
void doubleClick()
{
    log_d(" doubleClick");
    lastClickTime = 0;
}
void buttonHandle(void *params)
{
    WAIT_FLAG_SET(FLAG_INITIALIZED_STORE);
    EasyButton *button = (EasyButton *)params;
    int brightness = 0;  // how bright the LED is
    int fadeAmount = 10; // how many points to fade the LED by

    button->begin();
    button->onPressed([]()
                      { lastClickTime = millis(); });
    button->onPressedFor(PRESS_TIME, onPressed);
    button->onSequence(2, DOUBLE_CLICK_DURATION, doubleClick);
    while (1)
    {
                static UBaseType_t lastUxHighWaterMark = 0;
                UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
                if (lastUxHighWaterMark != uxHighWaterMark)
                {
                    lastUxHighWaterMark = uxHighWaterMark;
                    log_w("uxTaskGetStackHighWaterMark: %d", lastUxHighWaterMark);
                }
        vTaskDelay(50 / portTICK_PERIOD_MS);
        if (digitalRead(BUTTON_PIN) == 0)
        {
            countToFactoryReset++;
            if (countToFactoryReset >= 200)
            {
                countToFactoryReset = 200;
                brightness = 0;
                for (size_t i = 0; i < 20; i++)
                {
                    ledcWrite(LEDC_CHANNEL_0, 0);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
                    ledcWrite(LEDC_CHANNEL_0, 250);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
                }
                resetFactory();
            }
        }
        button->read();

        if (lastClickTime != 0 && millis() - lastClickTime > DOUBLE_CLICK_DURATION)
        {
            lastClickTime = 0;
            onClick();
        }
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 250)
        {
            fadeAmount = -fadeAmount;
        }
        ledcWrite(LEDC_CHANNEL_0, brightness);
    }
}
void setup_button()
{
    ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
    ledcAttachPin(LED_BUTTON_PIN, LEDC_CHANNEL_0);
    xTaskCreatePinnedToCore(
        buttonHandle,     /* Task function. */
        "buttonHandle",   /* name of task. */
        4096,             /* Stack size of task */
        (void *)&button,  /* parameter of the task */
        1,                /* priority of the task */
        NULL,             /* Task handle to keep track of created task */
        BUTTON_CORE_CPU); /* pin task to core 0 */
}