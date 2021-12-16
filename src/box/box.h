#pragma once
#include "box_env.h"
#include "ESP32_RMT_Driver.h"
#include "v_box.h"
#define RMT_CHANNEL RMT_CHANNEL_0
VBox layers[NUM_OF_LAYER] = {VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800)};

WS2812FX box = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
SemaphoreHandle_t control_layer_sem;

void boxShow()
{
    for (uint16_t i = 0; i < box.getNumBytes(); i++)
    {
        uint32_t sumPixelsValue = 0;
        uint32_t count = 0;
        for (size_t li = 0; li < NUM_OF_LAYER; li++)
        {
            if (layers[li].isRunning())
            {
                count++;
                sumPixelsValue += layers[li].getPixels()[i];
            }
        }
        if (count != 0)
            box.getPixels()[i] = sumPixelsValue / count;
    }
    rmt_write_sample(RMT_CHANNEL, box.getPixels(), box.getNumBytes(), false); // channel 0
}
void boxHandle(void *params)
{
    log_w("boxHandle is running on core: %d", xPortGetCoreID());
    VBox *_layers = (VBox *)params;
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {

        _layers[i].init();
        _layers[i].setBrightness(255);
        _layers[i].setSegment(0, 0, LED_COUNT - 1, FX_MODE_RAINBOW_CYCLE, BLACK, 1000, NO_OPTIONS);
        _layers[i].start();
    }

    box.init();
    rmt_tx_int(RMT_CHANNEL, box.getPin());
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        _layers[i].setCustomShow(boxShow);
    }
    // Box.setup();
    _layers[0].setMode(FX_MODE_COLOR_WIPE);
    _layers[0].setColor(GREEN);
    // layer1.setMode(FX_MODE_RUNNING_RANDOM);
    _layers[1].setMode(FX_MODE_FADE);
    _layers[2].setColor(BLUE);
    _layers[1].setSpeed(300);
    _layers[2].setMode(FX_MODE_BLINK);
    _layers[2].setColor(RED);
    _layers[2].setSpeed(300);

    while (1)
    {
        for (size_t i = 0; i < NUM_OF_LAYER; i++)
        {
            _layers[i].service();
        }
    }
}
void setup_box()
{
    BaseType_t xReturned;
    log_w("setup_box starting: %d", xPortGetCoreID());

    xReturned = xTaskCreatePinnedToCore(
        boxHandle,            /* Task function. */
        "boxHandle",          /* name of task. */
        50000,                /* Stack size of task */
        (void *)layers,       /* parameter of the task */
        0, /* priority of the task */
        NULL,                 /* Task handle to keep track of created task */
        BOX_CORE_CPU);        /* pin task to core 0 */
    control_layer_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(control_layer_sem);
    if (xReturned == pdPASS)
    {
        /* The task was created.  Use the task's handle to delete the task. */
        log_w("setup_box created: %d", xPortGetCoreID());
    }
    else
    {
        log_w("setup_box create faile: %d", xPortGetCoreID());
    }
}