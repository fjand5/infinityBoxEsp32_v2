#pragma once
#include "box_env.h"
#include "box_command.h"
#include "box_controler.h"
#include "driver_show.h"
#include "v_box.h"
#include "box_init.h"
#include "ultis.h"
#include "../control_button/control_button.h"
#include "../microphone/microphone.h"

#define FLAG_BOX_READY (1 << 0)
extern QueueHandle_t boxCommandQueue;
extern QueueHandle_t boxCommandResoponseQueue;
extern void box_nextMode(int8_t layer);
VBox layers[NUM_OF_LAYER] = {VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800)};
WS2812FX box = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
EventGroupHandle_t box_status;
TimerHandle_t nextModeTimer;

void boxHandle(void *params)
{
    VBox *_layers = (VBox *)params;
    vocaStatus.waitStatus(Status_Store_Initialized);
    log_w("Box is running on core: %d", xPortGetCoreID());
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        _layers[i].init();
        _layers[i].setBrightness(255);
        _layers[i].start();
    }

    box.init();
    rmt_tx_int(RMT_CHANNEL, box.getPin());
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        _layers[i].setCustomShow(boxShow);
    }
    init_layers(_layers);
    xEventGroupSetBits(box_status, FLAG_BOX_READY);
    boxCommandQueue = xQueueCreate(8, sizeof(BoxCommand));
    boxCommandResoponseQueue = xQueueCreate(1, sizeof(BoxCommand));
    log_w("Box has initialze !!!");
    while (1)
    {
        static UBaseType_t lastUxHighWaterMark = 0;
        UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        if (lastUxHighWaterMark != uxHighWaterMark)
        {
            lastUxHighWaterMark = uxHighWaterMark;
            log_w("uxTaskGetStackHighWaterMark: %d", lastUxHighWaterMark);
        }
        microphone.handleMicrophone([](double val, double freq){
            String tmp;
            for (size_t i = 0; i < val; i++)
            {
                tmp+="=";
            }
            
            log_w("handleMicrophone: %s", tmp.c_str());
            
        });
        command_handle(_layers);
        for (size_t i = 0; i < NUM_OF_LAYER; i++)
        {
            _layers[i].service();
        }
    }
}
void startNextModeTimer()
{
    xTimerStart(nextModeTimer, portMAX_DELAY);
    controlButton.setLedMode(LedMode_FadeFast);
}
void stopNextModeTimer()
{
    xTimerStop(nextModeTimer, portMAX_DELAY);
    controlButton.setLedMode(LedMode_Blink);
}
void setup_box()
{
    BaseType_t xReturned;
    log_w("setup_box starting: %d", xPortGetCoreID());
    box_status = xEventGroupCreate();

    controlButton.setClickEvent([]()
                                { box_nextMode(0); });
    controlButton.setDoubleClickEvent(
        []()
        {
            if (xTimerIsTimerActive(nextModeTimer) == pdTRUE)
            {
                stopNextModeTimer();
            }
            else
            {
                startNextModeTimer();
            }
        });

    nextModeTimer = xTimerCreate(
        "nextModeTimer",
        5000 / portTICK_PERIOD_MS,
        pdTRUE, (void *)1,
        [](TimerHandle_t xTimer)
        {
            box_nextMode(0);
        });
    xReturned = xTaskCreatePinnedToCore(
        boxHandle,      /* Task function. */
        "boxHandle",    /* name of task. */
        4096,           /* Stack size of task */
        (void *)layers, /* parameter of the task */
        0,              /* priority of the task */
        NULL,           /* Task handle to keep track of created task */
        BOX_CORE_CPU);  /* pin task to core 0 */
    if (xReturned == pdPASS)
    {
        /* The task was created.  Use the task's handle to delete the task. */
        log_w("setup_box created: %d", xPortGetCoreID());
        startNextModeTimer();
    }
    else
    {
        log_w("setup_box create faile: %d", xPortGetCoreID());
    }
}