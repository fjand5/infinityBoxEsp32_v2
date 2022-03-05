#ifndef  __OVER_FLOW_BEGIN
#define __OVER_FLOW_BEGIN
#include <WS2812FX.h>
#include "list_effect.h"
#include "utils.h"
#define OVER_FLOW_BEGIN_SPEED 100
void overflowBeginInit(WS2812FX *leds)
{
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = OVER_FLOW_BEGIN_SPEED;
    }
}
void overflowBeginOnBeat(WS2812FX *leds, double val, double freq)
{
    if (val < 5)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);

        // leds->setPixelColor(seg->stop, 0x0000ff);
        leds->setPixelColor(seg->start, 0x00ffff);
        seg->speed = (100 - val) / 2;
    }
}

uint16_t overflowBeginHandler(WS2812FX *leds)
{
    WS2812FX::Segment *seg = leds->getSegment(); // get the current segment
    WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime();
    int seglen = seg->stop - seg->start + 1;
    int *tmp = new int[seglen - 1];      // 0 -> 10
    for (int i = 0; i < seglen - 1; i++) // 0->10
    {
        tmp[i] = leds->getPixelColor(seg->start + i);
    }
    leds->setPixelColor(seg->start, segrt->counter_mode_step);
    for (int i = 1; i < seglen; i++) // 1->11
    {
        // 1->11   // 0->10
        leds->setPixelColor(seg->start + i, tmp[i - 1]);
    }

    segrt->counter_mode_step = 0;
    delete tmp;
    return seg->speed;
}
#endif