#include <WS2812FX.h>
#include "list_effect.h"
#include "utils.h"
#define OVER_FLOW_MID_SPEED 100
void overflowMidInit(WS2812FX *leds)
{
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = OVER_FLOW_MID_SPEED;
    }
}
void overflowMidOnBeat(WS2812FX *leds, double val, double freq)
{
    if (freq <= 2.0 || val <= 2.0)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        WS2812FX::Segment_runtime *segrt = leds->getSegmentRuntime(i);
        uint16_t length = seg->stop - seg->start + 1;
        // cường độ càng cao thì lấy chỉ số màu càng lớn
        uint32_t color = seg->colors[int(val) / 33 - 1];
        leds->setPixelColor(seg->start + length / 2, color);
        leds->setPixelColor(seg->start + length / 2 -1, color);
    }
}

uint16_t overflowMidHandler(WS2812FX *leds)
{
    WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
    int _seg_len = _seg->stop - _seg->start + 1;
    leds->copyPixels(_seg->start + _seg_len / 2 + 1 , _seg->start + _seg_len / 2, _seg_len / 2 - 1);
    leds->setPixelColor(_seg->start + _seg_len / 2, 0);
    for (uint16_t i = _seg_len / 2 ; i < _seg_len; i++)
    {
        uint32_t color = leds->getPixelColor(_seg->start + i);
        leds->setPixelColor(_seg->stop - i, color);
    }


    float total = countZeroPixel(leds,_seg->start,_seg->stop);
    total = total / (float)_seg_len;
    return OVER_FLOW_MID_SPEED*total;
}