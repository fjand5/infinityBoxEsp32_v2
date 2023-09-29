#ifndef REAL_BOX
#define REAL_BOX
#include "../box_env.h"
#include <functional>
#include <map>
#include <WS2812FX.h>
#include "driver_show.h"

#include "connect_virtual_box.h"
#include "microphone/microphone.h"
#define NUM_OF_COMMAND_WAITING 8


typedef struct
{
    uint32_t id;
    uint8_t colorIndex;
    uint32_t* colors;
    int8_t cmd;
    uint8_t layer;
    uint8_t brightness;
    uint8_t mode;
    uint8_t numSeg;
    bool musicModeState;
    bool rev;
    int8_t option;
    uint16_t speed;
    void *p;
} RealBoxCommandBundle;
typedef struct
{
    uint16_t start1;
    bool inv1;
    uint16_t start2;
    bool inv2;
    uint16_t start3;
    bool inv3;
    uint16_t start4;
    bool inv4;
} Face;
typedef std::function<void(RealBoxCommandBundle)> ResponseCommand;
typedef enum
{

    BoxCommand_Enable,
    BoxCommand_Disable,
    BoxCommand_SetMode,
    BoxCommand_GetMode,
    BoxCommand_RandomMode,
    BoxCommand_NextMode,
    BoxCommand_PreviousMode,
    BoxCommand_SetColor,
    BoxCommand_SetBrightness,
    BoxCommand_ConfigSegment,
    BoxCommand_ConfigShowFace,
    BoxCommand_SetSpeed,
    BoxCommand_SetMusicMode,
} BoxCommand;
class RealBox : public WS2812FX, public ConnectVirtualBox
{
private:
    RealBoxCommandBundle commandInfo;

    EventGroupHandle_t box_status;

    QueueHandle_t queueCommand;

    std::map<uint32_t, ResponseCommand> responseCommandIndex;
    static void boxShow();
    void responseResult(RealBoxCommandBundle realBoxCommandBundle);
    BaseType_t checkCommand(RealBoxCommandBundle *realBoxCommandBundle);
    void commandHandle();
    bool isCustomMode(uint8_t mode);


public:
    RealBox(uint16_t num_leds, uint8_t pin, neoPixelType type);
    ~RealBox();

    void boxHandle();
    void startNextModeTimer();
    void stopNextModeTimer();
    void feedCommand(RealBoxCommandBundle *realBoxCommandBundle, ResponseCommand cbResponseCommand);
    uint8_t getModeNum(String mode);
    void begin();
};
extern RealBox realBox;
// extern void box_nextMode(int8_t layer);
#endif