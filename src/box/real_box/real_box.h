#pragma once



#define BOX_ENABLE 1
#define BOX_DISABLE 2
#define BOX_SET_MODE 3
#define BOX_GET_MODE 4
#define BOX_SET_COLOR 5
#define BOX_SET_BRIGHTNESS 6
#define BOX_CONFIG_SEGMENT 7
#define BOX_CONFIG_SHOW_FACE 8
#define BOX_SET_SPEED 9

#include "../box_env.h"
#include <functional>
#include <map>
#include <WS2812FX.h>
#include "driver_show.h"

 #include "connect_virtual_box.h"
// #include "../ultis.h"

// #include "../../control_button/control_button.h"
// #include "../microphone/microphone.h"

#define FLAG_BOX_READY (1 << 0)
#define NUM_OF_COMMAND_WAITING 8

typedef struct
{
    uint32_t id;
    int8_t cmd;
    uint8_t layer;
    int8_t option;
    void *p;
} RealBoxCommandBundle;

typedef std::function<void(RealBoxCommandBundle)> ResponseCommand;

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
    bool checkCommand(RealBoxCommandBundle *realBoxCommandBundle);
    void commandHandle();
    void initVirtualBoxes();

public:
    RealBox(uint16_t num_leds, uint8_t pin, neoPixelType type);
    ~RealBox();

    void boxHandle();
    void startNextModeTimer();
    void stopNextModeTimer();
    void feedCommand(RealBoxCommandBundle* realBoxCommandBundle, ResponseCommand cbResponseCommand);
    void begin();
};
extern RealBox realBox;
// extern void box_nextMode(int8_t layer);
