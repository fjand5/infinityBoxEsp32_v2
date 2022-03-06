#include "music_box.h"

MusicBox musicBox;
int musicEffect;
WS2812FX *musicLayer;
MusicBox::MusicBox(/* args */)
{
}
void MusicBox::onBeat(double val, double freq)
{
    switch (musicEffect)
    {
    case MusicEffect_OverflowBegin:
        overflowBeginOnBeat(musicLayer, val, freq);
        break;
    case MusicEffect_OverflowMiddle:
        overflowMidOnBeat(musicLayer, val, freq);
        break;
    case MusicEffect_StarBeat:
        starBeatOnBeat(musicLayer, val, freq);
        break;

    default:
        break;
    }
};

uint16_t MusicBox::musicEffectShow()
{
    switch (musicEffect)
    {
    case MusicEffect_OverflowBegin:
        return overflowBeginHandler(musicLayer);
        break;
    case MusicEffect_OverflowMiddle:
        return overflowMidHandler(musicLayer);
        break;
    case MusicEffect_StarBeat:
        return starBeatHandler(musicLayer);
        break;

    default:
        return 0;
        break;
    }
};
void MusicBox::setMusicLayer(WS2812FX *layer)
{
    musicLayer = layer;
};
void MusicBox::setEffect(int mode)
{
    musicEffect = mode;
    switch (musicEffect)
    {
    case MusicEffect_OverflowBegin:
        overflowBeginInit(musicLayer);
        break;
    case MusicEffect_OverflowMiddle:
        overflowMidInit(musicLayer);
        break;
    case MusicEffect_StarBeat:
        starBeatInit(musicLayer);
        break;
    default:
        break;
    }
};
MusicBox::~MusicBox()
{
}
