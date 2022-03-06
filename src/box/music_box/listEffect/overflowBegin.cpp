#ifndef __OVER_FLOW_BEGIN
#define __OVER_FLOW_BEGIN
#include <WS2812FX.h>
#include "list_effect.h"
#include "utils.h"
#define OVER_FLOW_BEGIN_SPEED 65
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

        // cường độ càng cao thì lấy chỉ số màu càng lớn
        uint32_t color = seg->colors[int(val) / 33 - 1];
        leds->setPixelColor(seg->start, color);
        // seg->speed = OVER_FLOW_BEGIN_SPEED;
    }
}

uint16_t overflowBeginHandler(WS2812FX *leds)
{
    WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
    int _seg_len = _seg->stop - _seg->start + 1;
    leds->copyPixels(_seg->start + 1, _seg->start, _seg_len - 1);
    leds->setPixelColor(_seg->start, 0);
    return _seg->speed;
}
#endif