#include "connect_virtual_box.h"
#include "Arduino.h"

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
void ConnectVirtualBox::splitSegment(VirtualBox *layer, int type)
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
        tmp = vocaStore.getValue("seg_font_1", "15").toInt();
        opt = vocaStore.getValue("seg_font_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_top_4", "16").toInt();
        opt = vocaStore.getValue("seg_top_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_font_2", "14").toInt();
        opt = vocaStore.getValue("seg_font_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_left_2", "1").toInt();
        opt = vocaStore.getValue("seg_left_2_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_font_3", "13").toInt();
        opt = vocaStore.getValue("seg_font_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_bottom_3", "9").toInt();
        opt = vocaStore.getValue("seg_bottom_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_font_4", "12").toInt();
        opt = vocaStore.getValue("seg_font_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_right_1", "23").toInt();
        opt = vocaStore.getValue("seg_right_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_back_1", "4").toInt();
        opt = vocaStore.getValue("seg_back_1_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_left_4", "3").toInt();
        opt = vocaStore.getValue("seg_left_4_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_back_2", "5").toInt();
        opt = vocaStore.getValue("seg_back_2_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_top_2", "18").toInt();
        opt = vocaStore.getValue("seg_top_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_back_3", "6").toInt();
        opt = vocaStore.getValue("seg_back_3_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_right_3", "21").toInt();
        opt = vocaStore.getValue("seg_right_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_back_4", "7").toInt();
        opt = vocaStore.getValue("seg_back_4_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_bottom_1", "11").toInt();
        opt = vocaStore.getValue("seg_bottom_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_top_3", "17").toInt();
        opt = vocaStore.getValue("seg_top_3_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_left_3", "2").toInt();
        opt = vocaStore.getValue("seg_left_3_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_top_1", "19").toInt();
        opt = vocaStore.getValue("seg_top_1_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_right_4", "20").toInt();
        opt = vocaStore.getValue("seg_right_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_bottom_4", "8").toInt();
        opt = vocaStore.getValue("seg_bottom_4_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_left_1", "0").toInt();
        opt = vocaStore.getValue("seg_left_1_rev", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("seg_bottom_2", "10").toInt();
        opt = vocaStore.getValue("seg_bottom_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("seg_right_2", "22").toInt();
        opt = vocaStore.getValue("seg_right_2_rev", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
    }
}

void ConnectVirtualBox::enableVirtualBox(uint8_t index)
{

    virtualBoxes[index]->enable();
};

void ConnectVirtualBox::disableVirtualBox(uint8_t index)
{
    virtualBoxes[index]->disable();
};

uint8_t ConnectVirtualBox::getVirtualBoxMode(uint8_t index)
{
    return virtualBoxes[index]->getMode();
};

void ConnectVirtualBox::setVirtualBoxMode(uint8_t index, String mode, uint16_t *newSpeed)
{
    uint8_t modeInt = virtualBoxes[0]->getNumModeName(String(mode));
    struct SetModeBundle
    {
        VirtualBox *layer;
        uint8_t index;
        uint8_t mode;
    };
    SetModeBundle *setModeBundle = new SetModeBundle;
    setModeBundle->layer = virtualBoxes[index];
    setModeBundle->index = index;
    setModeBundle->mode = modeInt;
    if (newSpeed != NULL)
    {
        *newSpeed = virtualBoxes[index]->getSpeedByMode(setModeBundle->mode);
    }
    xTaskCreatePinnedToCore(
        [](void *p)
        {
            SetModeBundle *setModeBundle = (SetModeBundle *)p;
            uint8_t numOfSegment = setModeBundle->layer->getNumSegments();
            for (int i = 0; i < numOfSegment; i++)
            {

                uint16_t _newSpeed = setModeBundle->layer->getSpeedByMode(setModeBundle->mode);
                setModeBundle->layer->setMode(i, setModeBundle->mode);
                setModeBundle->layer->setSpeed(i, _newSpeed);

                delay(TRANSITION_TIME / numOfSegment);
            };
            delete setModeBundle;
            vTaskDelete(NULL);
        },
        "setVirtualBoxMode",
        4096,
        (void *)setModeBundle,
        2,
        NULL,
        BOX_CORE_CPU);
};

char *ConnectVirtualBox::nextVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{
    uint8_t currentMode = getVirtualBoxMode(index);
    currentMode++;
    if (currentMode >= virtualBoxes[0]->getModeCount())
        currentMode = 0;
    String tmp = virtualBoxes[0]->getModeName(currentMode);
    char *newMode = new char[tmp.length() + 1];
    strcpy(newMode, tmp.c_str());
    setVirtualBoxMode(index, tmp, newSpeed);
    return newMode;
};

char *ConnectVirtualBox::previousVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{
    int8_t currentMode = getVirtualBoxMode(index);
    currentMode--;
    if (currentMode <= 0)
        currentMode = virtualBoxes[0]->getModeCount() - 1;
    String tmp = virtualBoxes[0]->getModeName(currentMode);
    char *newMode = new char[tmp.length() + 1];
    strcpy(newMode, tmp.c_str());
    setVirtualBoxMode(index, tmp, newSpeed);
    return newMode;
};

void ConnectVirtualBox::setVirtualBoxColor(uint8_t indexLayer, uint8_t indexColor, uint32_t color)
{
    VirtualBox *layer = virtualBoxes[indexLayer];
    layer->setColorByIndex(indexColor, color);
};
void ConnectVirtualBox::setVirtualBoxBrightness(uint8_t index, uint8_t brightness)
{

    VirtualBox *layer = virtualBoxes[index];
    layer->setBrightness(brightness);
};
void ConnectVirtualBox::setVirtualBoxSpeed(uint8_t index, uint16_t speed)
{
    VirtualBox *layer = virtualBoxes[index];
    for (int i = 0; i < layer->getNumSegments(); i++)
    {
        layer->setSpeed(i, speed);
    }
}
void ConnectVirtualBox::setVirtualBoxesDisplay(void (*p)())
{
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->setCustomShow(p);
    }
}

void ConnectVirtualBox::serviceVirtualBoxes()
{
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->service();
    }
}
void ConnectVirtualBox::initVirtualBoxes()
{
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
        if (vocaStore.getValue(tmp, "true") == "true")
        {
            virtualBoxes[i]->enable();
        }
        else
        {
            virtualBoxes[i]->disable();
        }

        splitSegment(virtualBoxes[i]);

        tmp = String("mode_layer_") + i;
        setVirtualBoxMode(i, vocaStore.getValue(tmp, "Blink"), NULL);

        tmp = String("color0_layer_") + i;
        uint32_t color;
        color = stringToColor(vocaStore.getValue(tmp, "0xff0000"));
        setVirtualBoxColor(i, 0, color);

        tmp = String("color1_layer_") + i;
        color = stringToColor(vocaStore.getValue(tmp, "0x00ff00"));
        setVirtualBoxColor(i, 1, color);

        tmp = String("color2_layer_") + i;
        color = stringToColor(vocaStore.getValue(tmp, "0x0000ff"));
        setVirtualBoxColor(i, 1, color);

        tmp = String("brig_layer_") + i;
        setVirtualBoxBrightness(i, vocaStore.getValue(tmp, "50").toInt());
    }
};
void ConnectVirtualBox::beginVirtualBoxes()
{

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i] = new VirtualBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    }
    initVirtualBoxes();
};

ConnectVirtualBox::~ConnectVirtualBox()
{
}
