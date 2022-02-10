#ifndef BOX_CONTROLER
#define BOX_CONTROLER
#include "real_box/real_box.h"
#include "voca_core.h"
// #include "box_utils.h"

extern RealBox realBox;

void box_enable(int8_t layer)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_Enable;
    request->layer = layer;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("enLyr_") + result.layer, "true", false);
                            delete request;
                        });
}
void box_disable(int8_t layer)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_Disable;
    request->layer = layer;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("enLyr_") + result.layer, "false", false);
                            delete request;
                        });
}

void box_setMode(int8_t layer, uint8_t mode)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetMode;
    request->layer = layer;
    request->mode = mode;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("spdLyr_") + result.layer, String(result.speed), false);
                            vocaStore.setValue(String("mdLyr_") + result.layer, String(request->mode), false);
                            delete request;
                        });
}
void box_nextMode(int8_t layer)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_NextMode;
    request->layer = layer;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("spdLyr_") + result.layer, String(result.speed), false);
                            vocaStore.setValue(String("mdLyr_") + result.layer, String(result.mode), false);
                            delete request;
                        });
}
void box_prevMode(int8_t layer)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_PreviousMode;
    request->layer = layer;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("spdLyr_") + result.layer, String(result.speed), false);
                            vocaStore.setValue(String("mdLyr_") + result.layer, String(result.mode), false);
                            delete request;
                        });
}
void box_setColor(int8_t layer, int8_t colorIndex, String color)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetColor;
    request->layer = layer;
    request->option = colorIndex;
    request->color = realBox.stringToColor(color);
    realBox.feedCommand(request,
                        [colorIndex, request, color](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("cl") + colorIndex + "Lyr_" + result.layer, String(color), false);
                            delete request;
                        });
}

void box_setBrightness(int8_t layer, uint8_t brightness)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetBrightness;
    request->layer = layer;
    request->brightness = brightness;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("brgLyr_") + result.layer, String(result.brightness), false);
                            delete request;
                        });
}
void box_setSpeed(int8_t layer, uint16_t speed)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetSpeed;
    request->layer = layer;
    request->speed = speed;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("spdLyr_") + result.layer, String(result.speed), false);
                            vocaStore.setValue(String("spdLyr_") + result.layer + "_" + vocaStore.getValue(String("mdLyr_") + result.layer), String(result.speed), false);
                            delete request;
                        });
}
void box_config_segment(String key, String value)
{
    bool rev;
    uint8_t num;

    if (key.endsWith("_rv"))
    {
        String tmp = key;
        tmp.replace("_rv", "");
        rev = value == "true";
        num = vocaStore.getValue(tmp, "0").toInt();
    }
    else
    {

        rev = vocaStore.getValue(key + "_rv", "false") == "true";
        num = value.toInt();
    }

    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_ConfigSegment;
    request->rev = rev;
    request->numSeg = num;

    
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            sg_tp_4
                            sg_tp_4_rv
                            // vocaStore.setValue(key, value, true);
                            delete request;
                        });
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
#endif