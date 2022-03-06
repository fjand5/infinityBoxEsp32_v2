#include <Arduino.h>
#include <WS2812FX.h>
#include "./listEffect/list_effect.h"
typedef enum
{
    // Phải bắt đầu là 0 để có thể đếm
    MusicEffect_OverflowBegin = 0,
    MusicEffect_OverflowMiddle,
    MusicEffect_StarBeat,
    MusicEffect_StarBeat2,
    MusicEffect_SegmentBeat,
    MusicEffect_VUMeter,
    MusicEffect_ShinesOn,
    MusicEffect_ShinesOn1,
    MusicEffect_ShinesOn2,
    MusicEffect_RunSpeed,
    MusicEffect_Lazy,
    MusicEffect_RainBow,
    MusicEffect_RainBowRun,
    MusicEffect_VUMeterColumn,

    // Gía trị cuối dùng cho việc đếm
    MusicEffect_Count,
} MusicEffect;

class MusicBox
{
private:
public:
    MusicBox(/* args */);
    void onBeat(double val, double freq);
    static uint16_t musicEffectShow();
    static void setMusicLayer(WS2812FX* layer);
    static void setEffect(int mode);
    ~MusicBox();
};
extern MusicBox musicBox;
