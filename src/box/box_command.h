#pragma once
#include <Arduino.h>
#include "v_box.h"
#include "box_init.h"

#define BOX_ENABLE 1
#define BOX_DISABLE 2
#define BOX_SET_MODE 3
#define BOX_GET_MODE 4
#define BOX_SET_COLOR 5
#define BOX_SET_BRIGHTNESS 6
#define BOX_CONFIG_SEGMENT 7
#define BOX_CONFIG_SHOW_FACE 8
#define BOX_SET_SPEED 9
#define SEND_COMMAND_TO_BOX(command) \
    command.id = millis();           \
    xQueueSend(boxCommandQueue, (void *)&command, portMAX_DELAY);
#define BOX_RESPONSE_COMMAND(command) xQueueSend(boxCommandResoponseQueue, (void *)&command, portMAX_DELAY);

struct BoxCommand
{
    uint32_t id;
    int8_t cmd;
    int8_t layer;
    int8_t option;
    void *p;
};
struct Face
{
    uint16_t start1;
    bool inv1;
    uint16_t start2;
    bool inv2;
    uint16_t start3;
    bool inv3;
    uint16_t start4;
    bool inv4;
};

QueueHandle_t boxCommandQueue;
QueueHandle_t boxCommandResoponseQueue;
BoxCommand rxBoxCmd;
void command_handle(VBox *layers)
{
    if (xQueueReceive(boxCommandQueue,
                      &rxBoxCmd, 0))
    {
        if (rxBoxCmd.cmd == BOX_CONFIG_SEGMENT)
        {
            uint16_t num = *((uint16_t *)rxBoxCmd.p);
            bool rev = rxBoxCmd.option;
            for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
            {
                layers[i].resetSegments();
                layers[i].clear();
                layers[i].setSegment(0,
                                     LED_COUNT_ONE_SEG * num,
                                     LED_COUNT_ONE_SEG * (num + 1) - 1,
                                     FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, rev);
                layers[i].setConfigState(true);
            }
            BOX_RESPONSE_COMMAND(rxBoxCmd);
        }
        else if (rxBoxCmd.cmd == BOX_CONFIG_SHOW_FACE)
        {
            Face face = *((Face *)rxBoxCmd.p);
            for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
            {
                layers[i].resetSegments();
                layers[i].clear();
                layers[i].setSegment(0,
                                     LED_COUNT_ONE_SEG * face.start1,
                                     LED_COUNT_ONE_SEG * (face.start1 + 1) - 1,
                                     FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv1);
                layers[i].setSegment(1,
                                     LED_COUNT_ONE_SEG * face.start2,
                                     LED_COUNT_ONE_SEG * (face.start2 + 1) - 1,
                                     FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv2);
                layers[i].setSegment(2,
                                     LED_COUNT_ONE_SEG * face.start3,
                                     LED_COUNT_ONE_SEG * (face.start3 + 1) - 1,
                                     FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv3);
                layers[i].setSegment(3,
                                     LED_COUNT_ONE_SEG * face.start4,
                                     LED_COUNT_ONE_SEG * (face.start4 + 1) - 1,
                                     FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv4);
                layers[i].setConfigState(true);
            }
            BOX_RESPONSE_COMMAND(rxBoxCmd);
        }
        else
        {
            if (layers[rxBoxCmd.layer].getConfigState() == true)
            {
                layers[rxBoxCmd.layer].setConfigState(false);
                init_layers(layers);
            }

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
                uint8_t modeInt = layers[rxBoxCmd.layer].getMode();
                BoxCommand res;
                res.id = rxBoxCmd.id;
                res.p = &modeInt;
                BOX_RESPONSE_COMMAND(res);
            }
            else if (rxBoxCmd.cmd == BOX_SET_MODE)
            {
                char *modeStr = (char *)rxBoxCmd.p;
                uint8_t modeInt = layers[rxBoxCmd.layer].getNumModeName(String(modeStr));
                struct SetModeBundle
                {
                    VBox *layers;
                    uint8_t index;
                    uint8_t mode;
                    uint16_t speed;
                } setModeBundle;
                setModeBundle.layers = layers;
                setModeBundle.index = rxBoxCmd.layer;
                setModeBundle.mode = modeInt;
                setModeBundle.speed = rxBoxCmd.option;
                BOX_THREAD([](void *p)
                           {
                               SetModeBundle setModeBundle = *((SetModeBundle *)p);
                               uint8_t numOfSegment = setModeBundle.layers[setModeBundle.index].getNumSegments();
                               for (int i = 0; i < numOfSegment; i++)
                               {
                                   setModeBundle.layers[setModeBundle.index].setMode(i, setModeBundle.mode);
                                   setModeBundle.layers[setModeBundle.index].setSpeed(i, setModeBundle.speed);

                                   delay(TRANSITION_TIME / numOfSegment);
                               };
                               vTaskDelete(NULL);
                           },
                           &setModeBundle);
                BOX_RESPONSE_COMMAND(rxBoxCmd);
                
            }
            else if (rxBoxCmd.cmd == BOX_SET_COLOR)
            {
                layers[rxBoxCmd.layer].setColorByIndex(rxBoxCmd.option, *((uint32_t *)rxBoxCmd.p));
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_SET_BRIGHTNESS)
            {
                layers[rxBoxCmd.layer].setBrightness(*((uint8_t *)rxBoxCmd.p));
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }

            else if (rxBoxCmd.cmd == BOX_SET_SPEED)
            {
                setLayerSpeed(&layers[rxBoxCmd.layer], *((uint16_t *)rxBoxCmd.p));
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
            else
            {
                BOX_RESPONSE_COMMAND(rxBoxCmd);
            }
        }
    }
}