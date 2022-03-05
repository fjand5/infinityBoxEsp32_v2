#include "music_box.h"
MusicBox musicBox;
WS2812FX *musicLayer;
MusicBox::MusicBox(/* args */)
{
}
void MusicBox::onBeat(double val, double freq){
    if(val<5)
    return;
   for (int i = 0; i < musicLayer->getNumSegments(); i++)
    {
        WS2812FX::Segment *seg = musicLayer->getSegment(i);
        WS2812FX::Segment_runtime *segrt = musicLayer->getSegmentRuntime(i);

        // musicLayer->setPixelColor(seg->stop, 0x0000ff);
        musicLayer->setPixelColor(seg->start, 0x00ffff);
        seg->speed = (100 - val)/2;
    }

};

uint16_t MusicBox::musicEffectShow()
{
    // log_w("dang handle music box: %d", musicLayer);
    WS2812FX::Segment *seg = musicLayer->getSegment(); // get the current segment
    WS2812FX::Segment_runtime *segrt = musicLayer->getSegmentRuntime();
    int seglen = seg->stop - seg->start + 1;
    int *tmp = new int[seglen - 1];      // 0 -> 10
    for (int i = 0; i < seglen - 1; i++) // 0->10
    {
        tmp[i] = musicLayer->getPixelColor(seg->start + i);
    }
    musicLayer->setPixelColor(seg->start, segrt->counter_mode_step);
    for (int i = 1; i < seglen; i++) // 1->11
    {
        // 1->11   // 0->10
        musicLayer->setPixelColor(seg->start + i, tmp[i - 1]);
    }

    segrt->counter_mode_step = 0;
    delete tmp;
    return seg->speed;
};
void MusicBox::setMusicLayer(WS2812FX *layer)
{
    musicLayer = layer;
};
MusicBox::~MusicBox()
{
}
