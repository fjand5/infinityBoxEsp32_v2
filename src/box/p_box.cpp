#include "p_box.h"

PBox Box(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
PBox::PBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
           uint8_t max_num_segments,
           uint8_t max_num_active_segments) : WS2812FX(num_leds, pin, type,
                                                       max_num_segments,
                                                       max_num_active_segments)
{
    _vBoxes = new list<VBox>;
}
void PBox::service_handle()
{
    for (auto vBox = (*_vBoxes).begin();
         vBox != (*_vBoxes).end();
         ++vBox)
    {
        vBox->service();
    }
}
void PBox::addVBox(VBox vBox)
{
    (*_vBoxes).push_front(vBox);
}
void PBox::setup()
{

    for (auto vBox = (*_vBoxes).begin();
         vBox != (*_vBoxes).end();
         ++vBox)
    {
        vBox->init();
        vBox->setBrightness(64);
        vBox->start();
        vBox->setCustomShow(physShow);
    }
    setBrightness(255);
    setSegment(0, 0);
    start();
    rmt_tx_int(RMT_CHANNEL, getPin());
}

void physShow()
{
    list<VBox> *_vBoxes = Box.getVBoxes();
    for (uint16_t i = 0; i < Box.getNumBytes(); i++)
    {
        float sumPixelsValue = 0;
        for (auto vBox = (*_vBoxes).begin();
             vBox != (*_vBoxes).end();
             ++vBox)
        {
            sumPixelsValue += vBox->getPixels()[i];
        }
        Box.getPixels()[i] = sumPixelsValue / (*_vBoxes).size();
    }
    // Box.show();
    rmt_write_sample(RMT_CHANNEL, Box.getPixels(), Box.getNumBytes(), false); // channel 0
}
