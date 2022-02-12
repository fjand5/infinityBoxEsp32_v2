#ifndef CONNECT_VIRTUAL_BOX
#define CONNECT_VIRTUAL_BOX
#define SPLIT_SEGMENT_TYPE_VERTEX 0
#define SPLIT_SEGMENT_TYPE_FACE 1

#include "../box_env.h"

#include <WS2812FX.h>
#include <Arduino.h>

#include "../virtual_box/virtual_box.h"
#include "voca_store/voca_store.h"

class ConnectVirtualBox
{
private:
    bool _isConfig = false;
    void splitSegment(VirtualBox *layer, int type = SPLIT_SEGMENT_TYPE_VERTEX);
    DEFINE_DEFAULT_SPEED;
    DEFINE_DEFAULT_COLOR(MAX_NUM_COLORS);
protected:
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
    // config
    void configSegment(uint16_t num, bool rev);
    void configShowFace(Face face);

    void setConfigState(bool state)
    {
        _isConfig = state;
    };
    bool getConfigState()
    {
        return _isConfig;
    }

    // display
    static void mixVirtualBox(uint8_t *pPixels, const uint16_t numBytes);
    void setVirtualBoxesDisplay(void (*p)());
    void serviceVirtualBoxes();

    // control
    void enableVirtualBox(uint8_t index);
    void disableVirtualBox(uint8_t index);

    void setVirtualBoxSpeed(uint8_t index, uint16_t speed);

    uint8_t getVirtualBoxMode(uint8_t index);
    void setVirtualBoxMode(uint8_t index, uint8_t mode, uint16_t *newSpeed);



    uint8_t randomVirtualBoxMode(uint8_t index, uint16_t *newSpeed);
    uint8_t nextVirtualBoxMode(uint8_t index, uint16_t *newSpeed);
    uint8_t previousVirtualBoxMode(uint8_t index, uint16_t *newSpeed);

    uint32_t* setVirtualBoxColor(uint8_t indexLayer, uint8_t indexColor, uint32_t color);

    void setVirtualBoxBrightness(uint8_t index, uint8_t brightness);

    // initialze
    void initVirtualBoxes();
    void beginVirtualBoxes();

public:
    ConnectVirtualBox(/* args */);
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
    uint8_t getModeNum(String mode);
    ~ConnectVirtualBox();
};
#endif