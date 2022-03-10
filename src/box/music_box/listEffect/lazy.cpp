#include "list_effect.h"
#include "utils.h"

#include <WS2812FX.h>

#define LAZY_SPEED 35

void lazyInit(WS2812FX *leds)
{

  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *seg = leds->getSegment(i);
    seg->speed = LAZY_SPEED;
  }
}
void lazyOnBeat(WS2812FX *leds, double val, double freq)
{
  if (val <= 2.0)
    return;
  for (int i = 0; i < leds->getNumSegments(); i++)
  {
    WS2812FX::Segment *_seg = leds->getSegment(i);
    WS2812FX::Segment_runtime *_seg_rt = leds->getSegmentRuntime();

    int _seg_len = _seg->stop - _seg->start + 1;

    for (uint16_t j = 0; j < double(_seg_len) * val / 100.0; j++)
    {

      leds->setPixelColor(_seg->start + leds->random16(_seg_len), _seg->colors[int(val) / 33 - 1]);
    }

    // nếu âm lượng cao hơn 75% thì cho phép dịch luôn.
    if (val > 75.0)
    {
      _seg_rt->counter_mode_step = _seg_len;
    }
  }

  // for (int i = 0; i < leds->getNumSegments(); i++){
  //     WS2812FX::Segment* seg = leds->getSegment(i);
  //     WS2812FX::Segment_runtime* segrt = leds->getSegmentRuntime(i);
  //     segrt->counter_mode_step = val;
  //     seg->speed = seg->speed*0.9;
  // }
}

uint16_t lazyHandler(WS2812FX *leds)
{
  WS2812FX::Segment *_seg = leds->getSegment(); // get the current segment
  WS2812FX::Segment_runtime *_seg_rt = leds->getSegmentRuntime();
  int _seg_len = _seg->stop - _seg->start + 1;

  // nếu segment hết chỗ trống
  // cho phép dịch
  if (countZeroPixel(leds, _seg->start, _seg->stop) == 0)
  {
    _seg_rt->counter_mode_step = _seg_len;
  }
  // ngược lại thì fade
  else
  {
    blendRange(leds, _seg->start, _seg->stop, 0, 2);
  }

  // dịch đến hết.
  if (_seg_rt->counter_mode_step > 0)
  {
    _seg_rt->counter_mode_step--;
    leds->copyPixels(_seg->start + 1, _seg->start, _seg_len - 1);
    leds->setPixelColor(_seg->start, 0);

    return _seg->speed;
  }
  return 0;
}