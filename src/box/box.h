#pragma once
#include "box_env.h"
#include "box_command.h"
#include "driver_show.h"
#include "v_box.h"
#include "box_init.h"
#include "ultis.h"

#define FLAG_BOX_READY (1 << 0)
extern QueueHandle_t boxCommandQueue;
extern QueueHandle_t boxCommandResoponseQueue;

VBox layers[NUM_OF_LAYER] = {VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800)};
WS2812FX box = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
EventGroupHandle_t box_status;

void boxHandle(void *params)
{
    VBox *_layers = (VBox *)params;
    WAIT_FLAG_SET(FLAG_INITIALIZED_STORE);
    log_w("boxHandle is running on core: %d", xPortGetCoreID());
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
    while (1)
    {
        static UBaseType_t lastUxHighWaterMark = 0;
        UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        if (lastUxHighWaterMark != uxHighWaterMark)
        {
            lastUxHighWaterMark = uxHighWaterMark;
            log_w("uxTaskGetStackHighWaterMark: %d", lastUxHighWaterMark);
        }
        command_handle(_layers);
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
    box_status = xEventGroupCreate();
    xReturned = xTaskCreatePinnedToCore(
        boxHandle,      /* Task function. */
        "boxHandle",    /* name of task. */
        4096,          /* Stack size of task */
        (void *)layers, /* parameter of the task */
        1,              /* priority of the task */
        NULL,           /* Task handle to keep track of created task */
        BOX_CORE_CPU);  /* pin task to core 0 */
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