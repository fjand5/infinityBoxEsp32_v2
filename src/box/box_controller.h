#ifndef BOX_CONTROLER
#define BOX_CONTROLER
#include "real_box/real_box.h"
#include "voca_core.h"
// #include "box_utils.h"

extern RealBox realBox;


// std::string toString(unsigned long val)
// {
//     char num[16];
//     itoa(val, num, 10);
//     return std::string(num);
// }
void box_enable(int8_t layer)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_Enable;
    request->layer = layer;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            std::string key = "enLyr_";
                            key += toString(result.layer);
                            vocaStore.setValue(key, "true", false);
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
                            std::string key = "enLyr_";
                            key += toString(result.layer);
                            vocaStore.setValue(key, "false", false);
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
                            std::string key = "msMd_";
                            key += toString(result.layer);
                            vocaStore.setValue(
                                key,
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
                            std::string key = "spdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key, toString(result.speed), false);

                            key = "mdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key,toString(request->mode), false);
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
                            std::string key = "spdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key, toString(result.speed), false);

                            key = "mdLyr_";
                            
                            key += toString(result.layer);

                            vocaStore.setValue(key, toString(result.mode), false);

                            delete request;
                        });
}
void box_randomModeAll()
{
    for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
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
            pdTRUE, (void *)0,
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
                            std::string key = "spdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key, toString(result.speed), false);

                            key = "mdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key,  toString(result.mode), false);

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
                      
                            std::string key = "spdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key,  toString(result.speed), false);

                            key = "mdLyr_";
                            key +=  toString(result.layer);

                            vocaStore.setValue(key, toString(result.mode), false);

                            // vocaStore.setValue(String("spdLyr_") + result.layer, String(result.speed), false);
                            // vocaStore.setValue(String("mdLyr_") + result.layer, String(result.mode), false);
                            delete request;
                        });
}
void box_setColor(int8_t layer, int8_t colorIndex)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetColor;
    request->layer = layer;
    request->colorIndex = colorIndex;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            std::string key;

                            key = "cl0Lyr_";
                            key += toString(result.layer);
                            
                            vocaStore.setValue(key, colorBox.colorToString(result.colors[0]), false);

                            key = "cl1Lyr_";
                            key += toString(result.layer);
                            vocaStore.setValue(key, colorBox.colorToString(result.colors[1]), false);

                            key = "cl2Lyr_";
                            key += toString(result.layer);
                            vocaStore.setValue(key, colorBox.colorToString(result.colors[2]), false);

                            key = "clLyr_";
                            key += toString(result.layer);
                            vocaStore.setValue(key, toString(result.colorIndex), false);
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
                            char buff[8];
                            std::string key = "brgLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key, toString(result.brightness), false);
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
                            std::string key;
                            key = "spdLyr_";
                            key += toString(result.layer);

                            vocaStore.setValue(key, toString(result.speed), false);

                            key = "spdLyr_";
                            key += toString(result.layer);
                            key += "_";

                            // Lấy mode của layer hiện tại
                            int8_t mode;
                          
                            std::string modeKey = "mdLyr_";
                            modeKey += toString(result.layer);
                            if (vocaStore.checkKey(modeKey))
                            {
                                std::string value = vocaStore.getValue(modeKey);
                                mode = atoi(value.c_str());
                            }
                            else
                            {
                                mode = 0;
                            }
                            //===========================

                            key += toString(mode);
                            // char* layerIndex[4];
                            vocaStore.setValue(key, toString(result.speed), false);

                            // vocaStore.setValue(String("spdLyr_") + result.layer + "_" + vocaStore.getValue(String("mdLyr_") + result.layer), buff, false);
                            delete request;
                        });
}
// config segment
// void box_config_segment(const char* key, const char* value, void *param)
// {
//     bool rev;
//     uint8_t num;

//     char *segName;
//     if (key.endsWith("_rv"))
//     {
//         std::string tmp = key;
//         tmp.replace("_rv", "");
//         rev = value == "true";
//         num = vocaStore.getValue(tmp, "0").toInt();
//         segName = new char[tmp.length() + 1]();
//         strcpy(segName, tmp.c_str());
//     }
//     else
//     {

//         rev = vocaStore.getValue(key + "_rv", "false") == "true";
//         num = value.toInt();
//         segName = new char[key.length() + 1]();
//         strcpy(segName, key);
//     }

//     RealBoxCommandBundle *request = new RealBoxCommandBundle;
//     request->cmd = BoxCommand_ConfigSegment;
//     request->rev = rev;
//     request->numSeg = num;
//     realBox.feedCommand(request,
//                         [request, segName](RealBoxCommandBundle result)
//                         {
//                             String tmp = String(segName);
//                             vocaStore.setValue(tmp, String(result.numSeg), true);
//                             tmp += "_rv";
//                             vocaStore.setValue(tmp, String(result.rev ? "true" : "false"), true);
//                             delete request;
//                             delete segName;
//                         });
// }
// void box_config_show_face(String key, String value, void *param)
// {
//     key.replace("shw_", "");
//     Face *face = new Face;
//     face->start1 = vocaStore.getValue(key + "_1").toInt();
//     face->inv1 = vocaStore.getValue(key + "_1_rv") == "true";
//     face->start2 = vocaStore.getValue(key + "_2").toInt();
//     face->inv2 = vocaStore.getValue(key + "_2_rv") == "true";
//     face->start3 = vocaStore.getValue(key + "_3").toInt();
//     face->inv3 = vocaStore.getValue(key + "_3_rv") == "true";
//     face->start4 = vocaStore.getValue(key + "_4").toInt();
//     face->inv4 = vocaStore.getValue(key + "_4_rv") == "true";
//     RealBoxCommandBundle *request = new RealBoxCommandBundle;
//     request->cmd = BoxCommand_ConfigShowFace;
//     request->p = (void *)face;
//     realBox.feedCommand(request,
//                         [request, face](RealBoxCommandBundle result)
//                         {
//                             delete request;
//                             delete face;
//                         });
// }
// color
void box_setCurrentSelectColor(uint8_t index)
{
    vocaStore.setValue("clSel", toString(index));
    colorBox.setCurrentColorsIndex(index);
    uint32_t colors[MAX_NUM_COLORS];
    colorBox.readCurentColors(colors);

    for (uint8_t i = 0; i < MAX_NUM_COLORS; i++)
    {
        std::string key = "clSel";
        key += toString(i);
        std::string color = colorBox.colorToString(colors[i]);
        vocaStore.setValue(key, color, true);
    }
    vocaStore.updateStore();
}
void box_modifyColor(uint8_t indexColor, std::string colorString)
{
    uint32_t color[MAX_NUM_COLORS];
    colorBox.stringToColor(colorString, color);

    colorBox.modifyColor(indexColor, *color);
    std::string key = "clSel";
    key += toString(indexColor);
    vocaStore.setValue(key, colorString, true);
}
void box_defaultColor()
{
    colorBox.setDefault();
    uint32_t colors[MAX_NUM_COLORS];
    colorBox.readCurentColors(colors);

    for (uint8_t i = 0; i < MAX_NUM_COLORS; i++)
    {
        std::string key = "clSel";
        key += toString(i);
        std::string color = colorBox.colorToString(colors[i]);
        vocaStore.setValue(key, color, true);
    }
    vocaStore.updateStore();
}
void box_randomColorAll()
{

    for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
    {
        box_setColor(i, random(COLOR_COUNT));
    }
}
void box_setTimerRandomColor(bool state)
{
    static TimerHandle_t randomColorTimer = NULL;
    if (randomColorTimer == NULL)
    {
        randomColorTimer = xTimerCreate(
            "randomColorTimer",
            5000 / portTICK_PERIOD_MS,
            pdTRUE, (void *)0,
            [](TimerHandle_t xTimer)
            {
                box_randomColorAll();
            });
    }
    if (state)
    {
        xTimerStart(randomColorTimer, portMAX_DELAY);
        vocaStore.setValue("rndClTm", "true", true);
    }
    else
    {
        xTimerStop(randomColorTimer, portMAX_DELAY);
        vocaStore.setValue("rndClTm", "false", true);
    }
}
#endif