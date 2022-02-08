#include "connect_virtual_box.h"

static VirtualBox *virtualBoxes[NUM_OF_LAYER];

void ConnectVirtualBox::mixVirtualBox(uint8_t *pPixels, const uint16_t numBytes)
{
    for (uint16_t i = 0; i < numBytes; i++)
    {
        uint32_t sumPixelsValue = 0;
        uint32_t count = 0;
        for (size_t li = 0; li < NUM_OF_LAYER; li++)
        {
            if (virtualBoxes[li]->isRunning())
            {
                count++;
                sumPixelsValue += virtualBoxes[li]->getPixels()[i];
            }
        }
        if (count != 0)
            pPixels[i] = sumPixelsValue / count;
        else
            pPixels[i] = 0;
    }
}
ConnectVirtualBox::ConnectVirtualBox(/* args */)
{
}

void ConnectVirtualBox::configSegment(uint16_t num, bool rev)
{
    for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->resetSegments();
        virtualBoxes[i]->clear();
        virtualBoxes[i]->setSegment(0,
                                    LED_COUNT_ONE_SEG * num,
                                    LED_COUNT_ONE_SEG * (num + 1) - 1,
                                    FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, rev);
        setConfigState(true);
    }
};

void ConnectVirtualBox::configShowFace(Face face)
{
    for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->resetSegments();
        virtualBoxes[i]->clear();
        virtualBoxes[i]->setSegment(0,
                                    LED_COUNT_ONE_SEG * face.start1,
                                    LED_COUNT_ONE_SEG * (face.start1 + 1) - 1,
                                    FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv1);
        virtualBoxes[i]->setSegment(1,
                                    LED_COUNT_ONE_SEG * face.start2,
                                    LED_COUNT_ONE_SEG * (face.start2 + 1) - 1,
                                    FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv2);
        virtualBoxes[i]->setSegment(2,
                                    LED_COUNT_ONE_SEG * face.start3,
                                    LED_COUNT_ONE_SEG * (face.start3 + 1) - 1,
                                    FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv3);
        virtualBoxes[i]->setSegment(3,
                                    LED_COUNT_ONE_SEG * face.start4,
                                    LED_COUNT_ONE_SEG * (face.start4 + 1) - 1,
                                    FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv4);
        setConfigState(true);
    }
};
void ConnectVirtualBox::splitSegment(VirtualBox *layer, int type = SPLIT_SEGMENT_TYPE_VERTEX)
{
    int mode, color, speed;
    mode = layer->getMode();
    color = layer->getColor();
    speed = layer->getSpeed();
    if (type == SPLIT_SEGMENT_TYPE_VERTEX)
    {
        int tmp;
        uint8_t opt, index = 0;
        uint16_t offset = 0;
        // tmp = vocaStore.getValue("seg_font_1", "15").toInt();
        // opt = vocaStore.getValue("seg_font_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_top_4", "16").toInt();
        // opt = vocaStore.getValue("seg_top_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_font_2", "14").toInt();
        // opt = vocaStore.getValue("seg_font_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_left_2", "1").toInt();
        // opt = vocaStore.getValue("seg_left_2_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_font_3", "13").toInt();
        // opt = vocaStore.getValue("seg_font_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_bottom_3", "9").toInt();
        // opt = vocaStore.getValue("seg_bottom_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_font_4", "12").toInt();
        // opt = vocaStore.getValue("seg_font_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_right_1", "23").toInt();
        // opt = vocaStore.getValue("seg_right_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_back_1", "4").toInt();
        // opt = vocaStore.getValue("seg_back_1_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_left_4", "3").toInt();
        // opt = vocaStore.getValue("seg_left_4_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_back_2", "5").toInt();
        // opt = vocaStore.getValue("seg_back_2_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_top_2", "18").toInt();
        // opt = vocaStore.getValue("seg_top_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_back_3", "6").toInt();
        // opt = vocaStore.getValue("seg_back_3_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_right_3", "21").toInt();
        // opt = vocaStore.getValue("seg_right_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_back_4", "7").toInt();
        // opt = vocaStore.getValue("seg_back_4_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_bottom_1", "11").toInt();
        // opt = vocaStore.getValue("seg_bottom_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_top_3", "17").toInt();
        // opt = vocaStore.getValue("seg_top_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_left_3", "2").toInt();
        // opt = vocaStore.getValue("seg_left_3_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_top_1", "19").toInt();
        // opt = vocaStore.getValue("seg_top_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_right_4", "20").toInt();
        // opt = vocaStore.getValue("seg_right_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_bottom_4", "8").toInt();
        // opt = vocaStore.getValue("seg_bottom_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_left_1", "0").toInt();
        // opt = vocaStore.getValue("seg_left_1_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // tmp = vocaStore.getValue("seg_bottom_2", "10").toInt();
        // opt = vocaStore.getValue("seg_bottom_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        // tmp = vocaStore.getValue("seg_right_2", "22").toInt();
        // opt = vocaStore.getValue("seg_right_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
    }
}

void ConnectVirtualBox::setLayerMode(VirtualBox *layer, uint8_t mode)
{
    for (int i = 0; i < layer->getNumSegments(); i++)
    {
        layer->setMode(i, mode);
    }
}

void ConnectVirtualBox::setLayerSpeed(VirtualBox *layer, uint16_t speed)
{
    for (int i = 0; i < layer->getNumSegments(); i++)
    {
        layer->setSpeed(i, speed);
    }
}
void ConnectVirtualBox::setDisplay(void (*p)())
{
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->setCustomShow(p);
    }
}

void ConnectVirtualBox::service()
{
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->service();
    }
}
void ConnectVirtualBox::begin()
{

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i] = new VirtualBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    }

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->init();
        virtualBoxes[i]->setBrightness(255);
        virtualBoxes[i]->start();
    }
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tmp;
        tmp = String("en_layer_") + i;
        // if (vocaStore.getValue(tmp, "true") == "true")
        // {
        //     virtualBoxes[i]->enable();
        // }
        // else
        // {
        //     virtualBoxes[i]->disable();
        // }

        splitSegment(virtualBoxes[i]);

        tmp = String("mode_layer_") + i;
        uint8_t modeInt = 2; //  virtualBoxes[i]->getNumModeName(vocaStore.getValue(tmp, "Blink"));
        setLayerMode(virtualBoxes[i], modeInt);

        tmp = String("color0_layer_") + i;
        uint32_t color;
        // color = stringToColor(vocaStore.getValue(tmp, "0xff0000"));
        // setLayerColor(virtualBoxes[i], 0, color);

        tmp = String("color1_layer_") + i;
        // color = stringToColor(vocaStore.getValue(tmp, "0x00ff00"));
        // setLayerColor(virtualBoxes[i], 1, color);

        tmp = String("color2_layer_") + i;
        // color = stringToColor(vocaStore.getValue(tmp, "0x0000ff"));
        // setLayerColor(virtualBoxes[i], 2, color);

        tmp = String("brig_layer_") + i;
        // setLayerBrightness(&virtualBoxes[i]-> vocaStore.getValue(tmp, "50").toInt());
    }
};

ConnectVirtualBox::~ConnectVirtualBox()
{
}
