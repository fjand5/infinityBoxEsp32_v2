#include "virtual_box.h"
VirtualBox::VirtualBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
           uint8_t max_num_segments,
           uint8_t max_num_active_segments) : WS2812FX(num_leds, pin, type,
                                                       max_num_segments,
                                                       max_num_active_segments)
{
}
void VirtualBox::beforeService()
{
}
void VirtualBox::affterService()
{
    if (!_enable)
        strip_off();
}
void VirtualBox::enable()
{
    start();
    _enable = true;
}
void VirtualBox::disable()
{
    stop();
    _enable = false;
}
void VirtualBox::setColorByIndex(uint8_t index, uint32_t color)
{
    for (int i = 0; i < getNumSegments(); i++)
    {
        uint32_t *colors = getColors(i);
        colors[index] = color;
    }
}
void VirtualBox::handler()
{
    beforeService();
    service();
    affterService();
}
uint8_t VirtualBox::getNumModeName(String name){
    for (uint8_t i = 0; i < getModeCount(); i++)
    {
       if (String(_names[i]) == name)
        return i;
    }
    return 0;
};
