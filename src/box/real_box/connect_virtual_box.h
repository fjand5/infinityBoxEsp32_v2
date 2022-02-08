#define SPLIT_SEGMENT_TYPE_VERTEX 0
#define SPLIT_SEGMENT_TYPE_FACE 1

#include "../box_env.h"
#include <WS2812FX.h>
#include "../virtual_box/virtual_box.h"
class ConnectVirtualBox
{
private:
    bool _isConfig = false;
    void splitSegment(VirtualBox *layer, int type = SPLIT_SEGMENT_TYPE_VERTEX);

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
    void configSegment( uint16_t num, bool rev);
    void configShowFace( Face face);

    void setConfigState(bool state){
        _isConfig = state;
    };
    bool getConfigState(){
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
    void setVirtualBoxMode(uint8_t index, String mode);

    void setVirtualBoxColor(uint8_t indexLayer, uint8_t indexColor, uint32_t color);

    void setVirtualBoxBrightness(uint8_t index, uint8_t brightness);

    
    // initialze
    void initVirtualBoxes();
    void beginVirtualBoxes();

public:
    ConnectVirtualBox(/* args */);
    ~ConnectVirtualBox();
};