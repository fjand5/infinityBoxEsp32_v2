#pragma once
#include "box_env.h"
#include "driver_show.h"
#include "v_box.h"
#include "ultis.h"

#define FLAG_BOX_READY (1 << 0)

#define BOX_ENABLE 1
#define BOX_DISABLE 2
#define BOX_SET_MODE 3
#define BOX_GET_MODE 4
#define BOX_SET_COLOR 5
#define BOX_SET_BRIGHTNESS 6
#define SEND_COMMAND_TO_BOX(command) \
    command.id = millis();           \
    xQueueSend(boxCommandQueue, (void *)&command, portMAX_DELAY);
#define BOX_RESPONSE_COMMAND(command) xQueueSend(boxCommandResoponseQueue, (void *)&command, portMAX_DELAY);
QueueHandle_t boxCommandQueue;
QueueHandle_t boxCommandResoponseQueue;
struct BoxCommand
{
    uint32_t id;
    int8_t cmd;
    int8_t layer;
    int8_t option;
    void *p;
};

VBox layers[NUM_OF_LAYER] = {VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),
                             VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800)};
WS2812FX box = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
EventGroupHandle_t box_status;

void boxHandle(void *params)
{
    log_w("boxHandle is running on core: %d", xPortGetCoreID());
    VBox *_layers = (VBox *)params;
    WAIT_FLAG_SET(FLAG_INITIALIZED_STORE);
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
        String tmp;
        splitSegment(&_layers[i]);
        tmp = String("mode_layer_") + i;
        setLayerMode(&_layers[i], getValue(tmp, "1").toInt());

        tmp = String("color0_layer_") + i;
        uint32_t color;
        color = stringToColor(getValue(tmp, "0xff0000"));
        setLayerColor(&_layers[i], 0, color);

        tmp = String("color1_layer_") + i;
        color = stringToColor(getValue(tmp, "0x00ff00"));
        setLayerColor(&_layers[i], 1, color);

        tmp = String("color2_layer_") + i;
        color = stringToColor(getValue(tmp, "0x0000ff"));
        setLayerColor(&_layers[i], 2, color);

        tmp = String("en_layer_") + i;
        if (getValue(tmp, "true") == "true")
        {
            _layers[i].enable();
        }
        else
        {
            _layers[i].disable();
        }
        tmp = String("brig_layer_") + i;
        setLayerBrightness(&_layers[i], getValue(tmp, "50").toInt());
    }
    xEventGroupSetBits(box_status, FLAG_BOX_READY);
    boxCommandQueue = xQueueCreate(8, sizeof(BoxCommand));
    boxCommandResoponseQueue = xQueueCreate(1, sizeof(BoxCommand));
    BoxCommand rxBoxCmd;
    while (1)
    {

        if (xQueueReceive(boxCommandQueue,
                          &rxBoxCmd, 0))
        {
            if (rxBoxCmd.cmd == BOX_ENABLE)
            {
                layers[rxBoxCmd.layer].enable();
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_DISABLE)
            {
                layers[rxBoxCmd.layer].disable();
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_GET_MODE)
            {
                uint8_t modeInt = _layers[rxBoxCmd.layer].getMode();
                BoxCommand res;
                res.id = rxBoxCmd.id;
                res.p = &modeInt;
                BOX_RESPONSE_COMMAND(res);
            }
            else if (rxBoxCmd.cmd == BOX_SET_MODE)
            {
                char *modeStr = (char *)rxBoxCmd.p;
                uint8_t modeInt = _layers[rxBoxCmd.layer].getNumModeName(String(modeStr));
                for (int i = 0; i < _layers[rxBoxCmd.layer].getNumSegments(); i++)
                {
                    _layers[rxBoxCmd.layer].setMode(i, modeInt);
                };
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_SET_COLOR)
            {
                _layers[rxBoxCmd.layer].setColorByIndex(rxBoxCmd.option, *((uint32_t *)rxBoxCmd.p));
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_SET_BRIGHTNESS)
            {
                _layers[rxBoxCmd.layer].setBrightness(*((uint8_t *)rxBoxCmd.p));
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
        }
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
        70000,          /* Stack size of task */
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