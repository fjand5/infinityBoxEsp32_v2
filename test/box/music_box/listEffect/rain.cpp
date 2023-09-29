#include <WS2812FX.h>
#include "utils.h"
#include "list_effect.h"

#define RAIN_SPEED 110
void rainInit(WS2812FX *leds)
{
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = RAIN_SPEED;
    }
}
void rainOnBeat(WS2812FX *leds, double val, double freq)
{
    if (val <= 2.0)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        for (uint16_t j = 0; j < double(seglen) * val / 100; j++)
        {
            leds->setPixelColor(seg->start + leds->random16(seglen), seg->colors[leds->random16(3)]);
        }
    }
}

uint16_t rainHandler(WS2812FX *leds)
{
    WS2812FX::Segment *seg = leds->getSegment(); // get the current segment

    WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
    int _seg_len = _seg->stop - _seg->start + 1;
    leds->copyPixels(_seg->start + 1, _seg->start, _seg_len - 1);
    leds->setPixelColor(_seg->start, 0);
    blendRange(leds, _seg->start, _seg->stop, 0, 32);
    uint16_t numPixelZero = countZeroPixel(leds, _seg->start, _seg->stop);
    return seg->speed + numPixelZero;
}