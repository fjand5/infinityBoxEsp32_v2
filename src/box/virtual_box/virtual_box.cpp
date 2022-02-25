#include "virtual_box.h"
VirtualBox::VirtualBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
                       uint8_t max_num_segments,
                       uint8_t max_num_active_segments) : WS2812FX(num_leds, pin, type,
                                                                   max_num_segments,
                                                                   max_num_active_segments)
{
    speedOfMode = new uint16_t[getModeCount()];
    Sem_VirtualBox = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_VirtualBox);

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
uint16_t VirtualBox::getSpeedByMode(uint8_t mode)
{
    return speedOfMode[mode];
};
void VirtualBox::setSpeedForMode(uint8_t mode, uint16_t speed)
{
    speedOfMode[mode] = speed;
};
void VirtualBox::setMusicMode(bool state)
{
    _musicMode = state;
};
void VirtualBox::onBeat(double val, double freq)
{
    if (_musicMode == false)
        return;
};

void VirtualBox::controlVirtualBox(CbControlVirtualBox cbControlVirtualBox, void* param)
{
    if (xSemaphoreTake(Sem_VirtualBox, portMAX_DELAY) == pdTRUE)
    {
        cbControlVirtualBox(this, param);
        xSemaphoreGive(Sem_VirtualBox);
     
    }
};
