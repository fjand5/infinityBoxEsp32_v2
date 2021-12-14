#pragma once
#include "v_box.h"
#include <list>
#include <WS2812FX.h>
#include "ESP32_RMT_Driver.h"
#define RMT_CHANNEL RMT_CHANNEL_0

#define LED_COUNT 288
#define LED_PIN 23
using namespace std;
void physShow();
class PBox : public WS2812FX
{
private:
    list<VBox> *_vBoxes;

public:
    PBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
         uint8_t max_num_segments = MAX_NUM_SEGMENTS,
         uint8_t max_num_active_segments = MAX_NUM_ACTIVE_SEGMENTS);
    void setup();
    void service_handle();
    void addVBox(VBox vBox);
    list<VBox> *getVBoxes()
    {
        return _vBoxes;
    };
};
extern PBox Box;
