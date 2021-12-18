#include "v_box.h"
VBox::VBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
           uint8_t max_num_segments,
           uint8_t max_num_active_segments) : WS2812FX(num_leds, pin, type,
                                                       max_num_segments,
                                                       max_num_active_segments)
{
}
void VBox::beforeService()
{
}
void VBox::affterService()
{
    if (!_enable)
        strip_off();
}
void VBox::enable()
{
    start();
    _enable = true;
}
void VBox::disable()
{
    stop();
    _enable = false;
}
void VBox::setColorByIndex(uint8_t index, uint32_t color)
{
    for (int i = 0; i < getNumSegments(); i++)
    {
        uint32_t *colors = getColors(i);
        colors[index] = color;
    }
}
void VBox::handler()
{
    beforeService();
    service();
    affterService();
}
uint8_t VBox::getNumModeName(String name){
    for (uint8_t i = 0; i < getModeCount(); i++)
    {
       if (String(_names[i]) == name)
        return i;
    }
    return 0;
};
