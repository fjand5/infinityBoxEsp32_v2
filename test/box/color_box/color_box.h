#ifndef COLOR_BOX
#define COLOR_BOX
#include "Arduino.h"
#include <WS2812FX.h>

#include "../box_env.h"

#include "voca_store/voca_store.h"


class ColorBox
{
private:
    uint8_t _currentColorsIndex;
    DEFINE_DEFAULT_COLOR(MAX_NUM_COLORS);
public:
    ColorBox();
    void begin();
    void modifyColor(uint8_t indexColor, uint32_t color, bool save = true);
    void setDefault();
    void setCurrentColorsIndex(int8_t index);
    void readColors(uint8_t ColorsIndex, uint32_t* colors);
    void readCurentColors(uint32_t* colors);
    void stringToColor(std::string val, uint32_t* colors);
    std::string colorToString(uint32_t colors);
    ~ColorBox();
};
extern ColorBox colorBox;
#endif