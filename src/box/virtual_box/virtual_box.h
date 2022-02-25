#ifndef VIRTUAL_BOX
#define VIRTUAL_BOX
#include <WS2812FX.h>
#include <map>
#include <functional>

typedef std::function<void(void *virtualbox, void *pram)> CbControlVirtualBox;
class VirtualBox : public WS2812FX
{
private:
    /* data */
    void beforeService();
    void affterService();

    bool _enable = true;
    uint16_t* speedOfMode;

    bool _musicMode = false;
    SemaphoreHandle_t Sem_VirtualBox;
public:
    VirtualBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
               uint8_t max_num_segments = MAX_NUM_SEGMENTS,
               uint8_t max_num_active_segments = MAX_NUM_ACTIVE_SEGMENTS);             
    void handler();
    void enable();
    void disable();
    void setColorByIndex(uint8_t index, uint32_t color);
    uint16_t getSpeedByMode(uint8_t mode);
    void setSpeedForMode(uint8_t mode, uint16_t speed);

    void setMusicMode(bool state);
    void onBeat(double val, double freq);

    void controlVirtualBox(CbControlVirtualBox cbControlVirtualBox, void* param);

};
#endif