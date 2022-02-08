#ifndef REAL_BOX
#define REAL_BOX
#include "../box_env.h"
#include <functional>
#include <map>
#include <WS2812FX.h>
#include "driver_show.h"

#include "connect_virtual_box.h"
// #include "box_utils.h"

// #include "../../control_button/control_button.h"
// #include "../microphone/microphone.h"

#define FLAG_BOX_READY (1 << 0)
#define NUM_OF_COMMAND_WAITING 8



typedef struct
{
    uint32_t id;
    uint32_t color;
    int8_t cmd;
    uint8_t layer;
    uint8_t brightness;

    int8_t option;
    uint16_t speed;
    void *p;
} RealBoxCommandBundle;

typedef std::function<void(RealBoxCommandBundle)> ResponseCommand;
typedef enum
{

    BoxCommand_Enable,
    BoxCommand_Disable,
    BoxCommand_SetMode,
    BoxCommand_GetMode,
    BoxCommand_NextMode,
    BoxCommand_PreviousMode,
    BoxCommand_SetColor,
    BoxCommand_SetBrightness,
    BoxCommand_ConfigSegment,
    BoxCommand_ConfigShowFace,
    BoxCommand_SetSpeed,
} BoxCommand;
class RealBox : public WS2812FX, public ConnectVirtualBox
{
private:
    RealBoxCommandBundle commandInfo;

    EventGroupHandle_t box_status;
    TimerHandle_t nextModeTimer;

    QueueHandle_t queueCommand;
    QueueHandle_t queueResoponse;

    std::map<uint32_t, ResponseCommand> responseCommandIndex;
    static void IRAM_ATTR boxShow();

    void responseResult(RealBoxCommandBundle realBoxCommandBundle);
    BaseType_t checkCommand(RealBoxCommandBundle *realBoxCommandBundle);
    void commandHandle();

public:
    RealBox(uint16_t num_leds, uint8_t pin, neoPixelType type);
    ~RealBox();

    void boxHandle();
    void startNextModeTimer();
    void stopNextModeTimer();
    void feedCommand(RealBoxCommandBundle *realBoxCommandBundle, ResponseCommand cbResponseCommand);
    void begin();
};
extern RealBox realBox;
// extern void box_nextMode(int8_t layer);
#endif