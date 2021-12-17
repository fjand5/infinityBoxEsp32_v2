#pragma once
#include <WS2812FX.h>
class VBox : public WS2812FX
{
private:
    /* data */
    void beforeService();
    void affterService();

    bool _enable = true;
public:
    VBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
        uint8_t max_num_segments  = MAX_NUM_SEGMENTS,
        uint8_t max_num_active_segments = MAX_NUM_ACTIVE_SEGMENTS);
    void handler();
    void enable();
    void disable();
    void setColorByIndex(uint8_t index, uint32_t color);
};
