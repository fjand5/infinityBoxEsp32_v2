#pragma once
#include "real_box/real_box.h"
// #include "ultis.h"
#include "voca_core.h"
extern RealBox realBox;
void box_enable(int8_t layer)
{
    log_w("box_enable %d", layer);
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BOX_ENABLE;
    request->layer = layer;
    realBox.feedCommand(request,
                        [](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("en_layer_") + result.layer, "true", false);
                            log_w("box_enable complete %d", result.layer);
                        });
    delete request;
}
void box_disable(int8_t layer)
{
    log_w("box_disable %d", layer);
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BOX_DISABLE;
    request->layer = layer;
    realBox.feedCommand(request,
                        [](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("en_layer_") + result.layer, "false", false);
                            log_w("box_disable complete %d", result.layer);

                        });
    delete request;
}
int8_t box_getMode(int8_t layer)
{
    
    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_GET_MODE;
    // txBoxCmd.layer = layer;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {
    //     uint8_t curMode = *((uint8_t *)rxBoxCmd.p);
    //     return curMode;
    // }
    // return -1;
}

void box_setMode(int8_t layer, String mode)
{
    // uint16_t speed = vocaStore.getValue(String("speed_layer_") + layer + "_" + mode).toInt();

    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_SET_MODE;
    // txBoxCmd.layer = layer;
    // txBoxCmd.p = (void *)mode.c_str();
    // txBoxCmd.option = speed;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {
    //     vocaStore.setValue(String("speed_layer_") + layer, String(speed), false);

    //     vocaStore.setValue(String("mode_layer_") + layer, String(mode), false);
    // }
}
void box_nextMode(int8_t layer)
{
    // uint8_t curMode = box_getMode(layer);
    // curMode++;
    // if (curMode == box.getModeCount() - 1)
    //     curMode = 0;
    // String nm = box.getModeName(curMode);
    // box_setMode(layer, nm);
}
void box_prevMode(int8_t layer)
{
    // uint8_t curMode = box_getMode(layer);
    // curMode--;
    // if (curMode == 0)
    //     curMode = box.getModeCount() - 1;
    // String nm = box.getModeName(curMode);
    // box_setMode(layer, nm);
}
void box_setColor(int8_t layer, int8_t iColor, String color)
{
    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_SET_COLOR;
    // txBoxCmd.layer = layer;
    // txBoxCmd.option = iColor;
    // uint32_t colorInt = stringToColor(color);
    // txBoxCmd.p = (void *)&colorInt;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {

    //     vocaStore.setValue(String("color") + iColor + "_layer_" + layer, color, false);
    // }
}

void box_setBrightness(int8_t layer, uint8_t brightness)
{
    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_SET_BRIGHTNESS;
    // txBoxCmd.layer = layer;
    // txBoxCmd.p = (void *)&brightness;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {
    //     vocaStore.setValue(String("brig_layer_") + layer, String(brightness), true);
    // }
}
void box_setSpeed(int8_t layer, uint16_t speed)
{
    // speed = constrain(speed, 0, 65535);
    // String mode = vocaStore.getValue(String("mode_layer_") + layer);
    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_SET_SPEED;
    // txBoxCmd.layer = layer;
    // txBoxCmd.p = (void *)&speed;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {
    //     vocaStore.setValue(String("speed_layer_") + layer, String(speed), false);
    //     vocaStore.setValue(String("speed_layer_") + layer + "_" + mode, String(speed), false);
    // }
}
void box_config_segment(String key, String value)
{
    // bool rev;
    // uint16_t num;

    // if (key.endsWith("_rev"))
    // {
    //     String tmp = key;
    //     tmp.replace("_rev", "");
    //     rev = value == "true";
    //     num = vocaStore.getValue(tmp, "0").toInt();
    // }
    // else
    // {

    //     rev = vocaStore.getValue(key + "_rev", "false") == "true";
    //     num = value.toInt();
    // }
    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_CONFIG_SEGMENT;
    // txBoxCmd.option = rev;
    // txBoxCmd.p = (void *)&num;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {
    //     vocaStore.setValue(key, value, true);
    // }
}
void box_config_show_face(String key, String value)
{
    // key.replace("show_", "");
    // Face face;
    // face.start1 = vocaStore.getValue(key + "_1").toInt();
    // face.inv1 = vocaStore.getValue(key + "_1_rev") == "true";
    // face.start2 = vocaStore.getValue(key + "_2").toInt();
    // face.inv2 = vocaStore.getValue(key + "_2_rev") == "true";
    // face.start3 = vocaStore.getValue(key + "_3").toInt();
    // face.inv3 = vocaStore.getValue(key + "_3_rev") == "true";
    // face.start4 = vocaStore.getValue(key + "_4").toInt();
    // face.inv4 = vocaStore.getValue(key + "_4_rev") == "true";

    // RealBoxCommandBundle txBoxCmd, rxBoxCmd;
    // txBoxCmd.cmd = BOX_CONFIG_SHOW_FACE;
    // txBoxCmd.p = (void *)&face;
    // realBox.feedCommand(&txBoxCmd);
    // if (xQueueReceive(boxCommandResoponseQueue, &rxBoxCmd, portMAX_DELAY) &&
    //     rxBoxCmd.id == txBoxCmd.id)
    // {
    // }
}