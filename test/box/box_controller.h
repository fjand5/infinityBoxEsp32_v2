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
void box_setMusicMode(bool state)
{
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_SetMusicMode;
    request->musicModeState = state;
    realBox.feedCommand(request,
                        [request](RealBoxCommandBundle result)
                        {
                            vocaStore.setValue(
                                "msMd",
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
            15000 / portTICK_PERIOD_MS,
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
void box_config_segment(std::string key, std::string value, void *param)
{
    bool isConfigReverce = key.find("_rv") != std::string::npos;
    bool rev;
    uint8_t num;

    char *segKeyName;
    if (isConfigReverce)
    {
        std::string sgKey = key.substr(0, key.length() - 3); // bỏ 3 ký tự cuối: "_rv"
        rev = !value.compare("true");
        num = atoi(vocaStore.getValue(sgKey, "0").c_str());
        segKeyName = new char[sgKey.length() + 1]();
        strcpy(segKeyName, sgKey.c_str());
    }
    else
    {
        std::string rvKey = key;
        rvKey += "_rv";
        rev = !vocaStore.getValue( rvKey, "false").compare("true");
        num = atoi(value.c_str());
        segKeyName = new char[key.length() + 1]();
        strcpy(segKeyName, key.c_str());
    }
    RealBoxCommandBundle *request = new RealBoxCommandBundle;
    request->cmd = BoxCommand_ConfigSegment;
    request->rev = rev;
    request->numSeg = num;
    realBox.feedCommand(request,
                        [request, segKeyName](RealBoxCommandBundle result)
                        {
                            std::string key(segKeyName);
                            vocaStore.setValue(key, toString(result.numSeg), true);
                            key += "_rv";
                            vocaStore.setValue(key, std::string(result.rev ? "true" : "false"), true);
                            delete request;
                            delete segKeyName;
                        });
}
void box_config_show_face(std::string key, std::string value, void *param)
{
    std::string fcKey = key.substr(4); // bỏ 4 ký tự đầu: "_rv"

    Face *face = new Face;
    face->start1 = atoi(vocaStore.getValue(fcKey + "_1").c_str());
    face->inv1 = !vocaStore.getValue(fcKey + "_1_rv").compare("true");
    face->start2 = atoi(vocaStore.getValue(fcKey + "_2").c_str());
    face->inv2 = !vocaStore.getValue(fcKey + "_2_rv").compare("true");
    face->start3 = atoi(vocaStore.getValue(fcKey + "_3").c_str());
    face->inv3 = !vocaStore.getValue(fcKey + "_3_rv").compare("true");
    face->start4 = atoi(vocaStore.getValue(fcKey + "_4").c_str());
    face->inv4 = !vocaStore.getValue(fcKey + "_4_rv").compare("true");
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
            15000 / portTICK_PERIOD_MS,
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