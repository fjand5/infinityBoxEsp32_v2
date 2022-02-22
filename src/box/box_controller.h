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
void box_setMusicMode(int8_t layer, bool state)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetMusicMode;
    request->layer = layer;
    request->musicModeState = state;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(
                                String("msMd_") + result.layer,
                                result.musicModeState ? "true" : "false",
                                false);
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
void box_randomMode(int8_t layer)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_RandomMode;
    request->layer = layer;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(String("spdLyr_") + result.layer, String(result.speed), false);
                            vocaStore.setValue(String("mdLyr_") + result.layer, String(result.mode), false);
                            delete request;
                        });
}
void box_randomModeAll()
{

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        box_randomMode(i);
    }
}
void box_setTimerRandomMode(bool state)
{
    static TimerHandle_t randomModeTimer = NULL;
    if (randomModeTimer == NULL)
    {
        randomModeTimer = xTimerCreate(
            "randomModeTimer",
            5000 / portTICK_PERIOD_MS,
            pdTRUE, (void *)1,
            [](TimerHandle_t xTimer)
            {
                box_randomModeAll();
            });
    }
    if (state)
    {
        xTimerStart(randomModeTimer, portMAX_DELAY);
    }
    else
    {
        xTimerStop(randomModeTimer, portMAX_DELAY);
    }
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
void box_setColor(int8_t layer, int8_t colorIndex)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetColor;
    request->layer = layer;
    request->option = colorIndex;
    request->colorIndex = colorIndex;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            char str[8];
                            sprintf(str, "#%06x", result.colors[0]);
                            vocaStore.setValue(String("cl0Lyr_") + result.layer, String(str), false);
                            sprintf(str, "#%06x", result.colors[1]);
                            vocaStore.setValue(String("cl1Lyr_") + result.layer, String(str), false);
                            sprintf(str, "#%06x", result.colors[2]);
                            vocaStore.setValue(String("cl2Lyr_") + result.layer, String(str), false);
                            vocaStore.setValue(String("clLyr_") + result.layer, String(result.colorIndex), false);
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
void box_config_segment(String key, String value, void* param)
{
    bool rev;
    uint8_t num;

    char *segName;
    if (key.endsWith("_rv"))
    {
        String tmp = key;
        tmp.replace("_rv", "");
        rev = value == "true";
        num = vocaStore.getValue(tmp, "0").toInt();
        segName = new char[tmp.length() + 1]();
        strcpy(segName, tmp.c_str());
    }
    else
    {

        rev = vocaStore.getValue(key + "_rv", "false") == "true";
        num = value.toInt();
        segName = new char[key.length() + 1]();
        strcpy(segName, key.c_str());
    }

    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_ConfigSegment;
    request->rev = rev;
    request->numSeg = num;
    realBox.feedCommand(request,
                        [request, segName](RealBoxCommandBundle result)
                        {
                            String tmp = String(segName);
                            vocaStore.setValue(tmp, String(result.numSeg), true);
                            tmp += "_rv";
                            vocaStore.setValue(tmp, String(result.rev ? "true" : "false"), true);
                            delete request;
                            delete segName;
                        });
}
void box_config_show_face(String key, String value, void* param)
{
    key.replace("shw_", "");
    Face *face = new Face;
    face->start1 = vocaStore.getValue(key + "_1").toInt();
    face->inv1 = vocaStore.getValue(key + "_1_rv") == "true";
    face->start2 = vocaStore.getValue(key + "_2").toInt();
    face->inv2 = vocaStore.getValue(key + "_2_rv") == "true";
    face->start3 = vocaStore.getValue(key + "_3").toInt();
    face->inv3 = vocaStore.getValue(key + "_3_rv") == "true";
    face->start4 = vocaStore.getValue(key + "_4").toInt();
    face->inv4 = vocaStore.getValue(key + "_4_rv") == "true";
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_ConfigShowFace;
    request->p = (void *)face;
    realBox.feedCommand(request,
                        [request, face](RealBoxCommandBundle result)
                        {
                            delete request;
                            delete face;
                        });
}
#endif