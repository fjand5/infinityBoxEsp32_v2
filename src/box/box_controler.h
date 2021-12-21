#pragma once
#include "box.h"
#include "ultis.h"
#include "voca_core.h"
extern WS2812FX box;
void box_enable(int8_t layer)
{
    BoxCommand txBoxCmd, rxBoxCmd;

    txBoxCmd.cmd = BOX_ENABLE;
    txBoxCmd.layer = layer;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        setValue(String("en_layer_") + layer, "true");
    }
}
void box_disable(int8_t layer)
{
    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_DISABLE;
    txBoxCmd.layer = layer;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        setValue(String("en_layer_") + layer, "false");
    }
}
void box_setMode(int8_t layer, String mode)
{
    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_SET_MODE;
    txBoxCmd.layer = layer;
    txBoxCmd.p = (void *)mode.c_str();
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        setValue(String("mode_layer_") + layer, String(mode));
    }
}
uint8_t box_getMode(int8_t layer)
{
    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_GET_MODE;
    txBoxCmd.layer = layer;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        uint8_t curMode = *((uint8_t *)rxBoxCmd.p);
        return curMode;
    }
    return -1;
}
void box_nextMode()
{
    uint8_t curMode = box_getMode(0);
    curMode++;
    String nm = box.getModeName(curMode);
    box_setMode(0, nm);
}
void box_setColor(int8_t layer, int8_t iColor, String color)
{
    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_SET_COLOR;
    txBoxCmd.layer = layer;
    txBoxCmd.option = iColor;
    uint32_t colorInt = stringToColor(color);
    txBoxCmd.p = (void *)&colorInt;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        setValue(String("color") + iColor + "_layer_" + layer, color);
    }
}

void box_setBrightness(int8_t layer, uint8_t brightness)
{
    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_SET_BRIGHTNESS;
    txBoxCmd.layer = layer;
    txBoxCmd.p = (void *)&brightness;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        setValue(String("brig_layer_") + layer, String(brightness));
    }
}
void box_config_segment(String key, String value)
{
    bool rev;
    uint16_t num;

    if (key.endsWith("_rev"))
    {
        String tmp = key;
        tmp.replace("_rev", "");
        rev = value == "true";
        num = getValue(tmp, "0").toInt();
    }
    else
    {

        rev = getValue(key + "_rev", "false") == "true";
        num = value.toInt();
    }
    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_CONFIG_SEGMENT;
    txBoxCmd.option = rev;
    txBoxCmd.p = (void *)&num;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
        setValue(key, value);
    }
}
void box_config_show_face(String key, String value)
{
    key.replace("show_", "");
    Face face;
    face.start1=getValue(key + "_1").toInt();
    face.inv1=getValue(key + "_1_rev") == "true";
    face.start2=getValue(key + "_2").toInt();
    face.inv2=getValue(key + "_2_rev") == "true";
    face.start3=getValue(key + "_3").toInt();
    face.inv3=getValue(key + "_3_rev") == "true";
    face.start4=getValue(key + "_4").toInt();
    face.inv4=getValue(key + "_4_rev") == "true";

    BoxCommand txBoxCmd, rxBoxCmd;
    txBoxCmd.cmd = BOX_CONFIG_SHOW_FACE;
    txBoxCmd.p = (void *)&face;
    SEND_COMMAND_TO_BOX(txBoxCmd);
    if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
        rxBoxCmd.id == txBoxCmd.id)
    {
    }
}