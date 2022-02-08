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

    static void mixVirtualBox(uint8_t *pPixels, const uint16_t numBytes);
    void setLayerMode(VirtualBox *layer, uint8_t mode);
    void setLayerSpeed(VirtualBox *layer, uint16_t speed);


    void configSegment( uint16_t num, bool rev);
    void configShowFace( Face face);

    void setConfigState(bool state){
        _isConfig = state;
    };
    bool getConfigState(){
        return _isConfig;
    }
    
    void setDisplay(void (*p)());
    void service();


public:
    ConnectVirtualBox(/* args */);
    void begin();
    ~ConnectVirtualBox();
};