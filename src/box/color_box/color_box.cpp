#include "color_box.h"
ColorBox colorBox;
ColorBox::ColorBox()
{
}
void ColorBox::begin()
{
    std::string key = "clSel";
    if (vocaStore.checkKey(key))
    {
        std::string value = vocaStore.getValue(key);
        setCurrentColorsIndex(atoi(value.c_str()));
    }
    else
    {
        setCurrentColorsIndex(0);
    }
};

void ColorBox::modifyColor(uint8_t indexColor, uint32_t color, bool save)
{
    std::string key = "clLst";
    key += toString(_currentColorsIndex);
    key += "_";
    key += toString(indexColor);

    std::string colorStr = colorToString(color);
    vocaStore.setValue(key, colorStr, save);
};

void ColorBox::setDefault()
{
    for (uint8_t i = 0; i < MAX_NUM_COLORS; i++)
    {
        modifyColor(i, listDefaulColors[_currentColorsIndex][i], false);
    }
    vocaStore.updateStore();
};
void ColorBox::setCurrentColorsIndex(int8_t currentColorsIndex)
{
    if (currentColorsIndex >= COLOR_COUNT)
        currentColorsIndex = COLOR_COUNT - 1;
    if (currentColorsIndex < 0)
        currentColorsIndex = 0;
    _currentColorsIndex = currentColorsIndex;
};
void ColorBox::readColors(uint8_t colorsIndex, uint32_t *colors)
{
    for (uint8_t i = 0; i < MAX_NUM_COLORS; i++)
    {
        std::string key = "clLst";
        key += toString(colorsIndex);
        key += "_";
        key += toString(i);

        std::string value = vocaStore.getValue(key, colorToString(listDefaulColors[colorsIndex][i]), true);
        stringToColor(value, (colors + i));
    }
};

void ColorBox::readCurentColors(uint32_t *colors)
{
    readColors(_currentColorsIndex, colors);
};
void ColorBox::stringToColor(std::string val, uint32_t *colors)
{

    std::transform(val.begin(), val.end(), val.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    // #ffaabb
    if (val.find("#") == std::string::npos || val.length() != 7)
        val = "#ff0000";
    std::string redStr = val.substr(1, 2);
    std::string greenStr = val.substr(3, 2);
    std::string blueStr = val.substr(5);
    int redInt = strtol(redStr.c_str(), NULL, 16);
    int greenInt = strtol(greenStr.c_str(), NULL, 16);
    int blueInt = strtol(blueStr.c_str(), NULL, 16);
    *colors = ((uint32_t)redInt << 16) | ((uint32_t)greenInt << 8) | blueInt;
}
std::string ColorBox::colorToString(uint32_t color)
{
    if(color>0xffffff)
        color = 0xffffff;
    char buff[8];
    sprintf(buff, "#%06x", color);
    return std::string(buff);
};
ColorBox::~ColorBox()
{
}
