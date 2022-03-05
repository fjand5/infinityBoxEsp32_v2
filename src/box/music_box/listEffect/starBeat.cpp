#include <WS2812FX.h>
#include "utils.h"
#include "list_effect.h"

#define STAR_BEAT_SPEED 10
void starBeatInit(WS2812FX *leds)
{
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        seg->speed = STAR_BEAT_SPEED;
    }
}
void starBeatOnBeat(WS2812FX *leds, double val, double freq)
{
    if (val <= 5.0)
        return;
    for (int i = 0; i < leds->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = leds->getSegment(i);
        int seglen = seg->stop - seg->start + 1;
        for (uint16_t j = 0; j < double(seglen) * val / 1000; j++)
        {

            leds->setPixelColor(seg->start + leds->random16(seglen), seg->colors[leds->random16(3)]);
        }
    }
}

uint16_t starBeatHandler(WS2812FX *leds)
{
    WS2812FX::Segment *seg = leds->getSegment(); // get the current segment
    int numPixelZero = 0;
    for (int j = seg->start; j <= seg->stop; j++)
    {
        if (leds->getPixelColor(j) == 0)
            numPixelZero++;
        uint32_t color = leds->getPixelColor(j);
        color = leds->color_blend(color, 0, 32);
        leds->setPixelColor(j, color);
    }
    return seg->speed + numPixelZero;
}