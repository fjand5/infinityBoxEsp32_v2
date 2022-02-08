#pragma once
#include "Arduino.h"

#define BOX_THREAD(func, param) xTaskCreatePinnedToCore( \
    func,                                                \
    "THREAD_LAYERS",                                     \
    4096,                           \ 
        (void *)param,                                   \
    2,                                                   \
    NULL,                                  \
    BOX_CORE_CPU);
uint32_t stringToColor(String val)
{
    // #ffaabb
    val.toLowerCase();
    if (!val.startsWith("#") || val.length() != 7)
        val = "#ff0000";
    uint32_t color;
    String redStr = val.substring(1, 3);
    String greenStr = val.substring(3, 5);
    String blueStr = val.substring(5);
    int redInt = strtol(redStr.c_str(), NULL, 16);
    int greenInt = strtol(greenStr.c_str(), NULL, 16);
    int blueInt = strtol(blueStr.c_str(), NULL, 16);
    color = ((uint32_t)redInt << 16) | ((uint32_t)greenInt << 8) | blueInt;
    return color;
}
void setLayerBrightness(VirtualBox *layer, uint8_t brig)
{
    layer->setBrightness(brig);
}
void setLayerColor(VirtualBox *layer, uint8_t index, uint32_t color)
{
    for (int i = 0; i < layer->getNumSegments(); i++)
    {
        layer->setColorByIndex(index, color);
    }
}