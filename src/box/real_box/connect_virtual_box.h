#ifndef CONNECT_VIRTUAL_BOX
#define CONNECT_VIRTUAL_BOX
#define SPLIT_SEGMENT_TYPE_VERTEX 0
#define SPLIT_SEGMENT_TYPE_FACE 1

#include "../box_env.h"

#include <WS2812FX.h>
#include <Arduino.h>

#include "../virtual_box/virtual_box.h"

#include "../color_box/color_box.h"

#include "voca_store/voca_store.h"
#include "../music_box/music_box.h"
extern ColorBox colorBox;
extern MusicBox musicBox;

class ConnectVirtualBox
{
private:
    bool _isConfig = false;
    bool _isMusicMode = false;
    void splitSegment(VirtualBox *layer, int type = SPLIT_SEGMENT_TYPE_VERTEX);
    SemaphoreHandle_t Sem_WaitSetModeFinish;

    DEFINE_DEFAULT_SPEED;
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
    // music
    void setMusicMode(bool state);
    // display
    static void mixVirtualBox(uint8_t *pPixels, const uint16_t numBytes);
    void setVirtualBoxesDisplay(void (*p)());
    void serviceVirtualBoxes();
    // music
    void onBeatVirtualBoxes(double val, double freq);
    // control
    void enableVirtualBox(uint8_t index);
    void disableVirtualBox(uint8_t index);

    void setVirtualBoxSpeed(uint8_t index, uint16_t speed);

    uint8_t getVirtualBoxMode(uint8_t index);
    void setVirtualBoxMode(uint8_t index, uint8_t mode, uint16_t *newSpeed, bool wait = false);



    uint8_t randomVirtualBoxMode(uint8_t index, uint16_t *newSpeed);
    uint8_t nextVirtualBoxMode(uint8_t index, uint16_t *newSpeed);
    uint8_t previousVirtualBoxMode(uint8_t index, uint16_t *newSpeed);

    void setVirtualBoxColor(uint8_t indexLayer, uint8_t indexColor, uint32_t *colors);

    void setVirtualBoxBrightness(uint8_t index, uint8_t brightness);

    // initialze
    void initVirtualBoxes();
    void beginVirtualBoxes();

public:
    ConnectVirtualBox(/* args */);
    uint8_t getModeNum(String mode);
    ~ConnectVirtualBox();
};
#endif