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
        tmp = vocaStore.getValue("sg_ft_1", "15").toInt();
        opt = vocaStore.getValue("sg_ft_1_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_tp_4", "16").toInt();
        opt = vocaStore.getValue("sg_tp_4_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_ft_2", "14").toInt();
        opt = vocaStore.getValue("sg_ft_2_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_lf_2", "1").toInt();
        opt = vocaStore.getValue("sg_lf_2_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_ft_3", "13").toInt();
        opt = vocaStore.getValue("sg_ft_3_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_bt_3", "9").toInt();
        opt = vocaStore.getValue("sg_bt_3_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_ft_4", "12").toInt();
        opt = vocaStore.getValue("sg_ft_4_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_rg_1", "23").toInt();
        opt = vocaStore.getValue("sg_rg_1_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_bk_1", "4").toInt();
        opt = vocaStore.getValue("sg_bk_1_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_lf_4", "3").toInt();
        opt = vocaStore.getValue("sg_lf_4_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_bk_2", "5").toInt();
        opt = vocaStore.getValue("sg_bk_2_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_tp_2", "18").toInt();
        opt = vocaStore.getValue("sg_tp_2_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_bk_3", "6").toInt();
        opt = vocaStore.getValue("sg_bk_3_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_rg_3", "21").toInt();
        opt = vocaStore.getValue("sg_rg_3_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_bk_4", "7").toInt();
        opt = vocaStore.getValue("sg_bk_4_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_bt_1", "11").toInt();
        opt = vocaStore.getValue("sg_bt_1_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_tp_3", "17").toInt();
        opt = vocaStore.getValue("sg_tp_3_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_lf_3", "2").toInt();
        opt = vocaStore.getValue("sg_lf_3_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_tp_1", "19").toInt();
        opt = vocaStore.getValue("sg_tp_1_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_rg_4", "20").toInt();
        opt = vocaStore.getValue("sg_rg_4_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_bt_4", "8").toInt();
        opt = vocaStore.getValue("sg_bt_4_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_lf_1", "0").toInt();
        opt = vocaStore.getValue("sg_lf_1_rv", "false") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        tmp = vocaStore.getValue("sg_bt_2", "10").toInt();
        opt = vocaStore.getValue("sg_bt_2_rv", "true") == "true";
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        tmp = vocaStore.getValue("sg_rg_2", "22").toInt();
        opt = vocaStore.getValue("sg_rg_2_rv", "true") == "true";
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

void ConnectVirtualBox::setVirtualBoxMode(uint8_t index, uint8_t mode, uint16_t *newSpeed)
{
    struct SetModeBundle
    {
        VirtualBox *layer;
        uint8_t index;
        uint8_t mode;
    };
    SetModeBundle *setModeBundle = new SetModeBundle;
    setModeBundle->layer = virtualBoxes[index];
    setModeBundle->index = index;
    setModeBundle->mode = mode;
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

uint8_t ConnectVirtualBox::nextVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{
    uint8_t currentMode = getVirtualBoxMode(index);
    currentMode++;
    if (currentMode >= FX_MODE_CUSTOM)
        currentMode = 0;
    ;
    setVirtualBoxMode(index, currentMode, newSpeed);
    return currentMode;
};
uint8_t ConnectVirtualBox::randomVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{
    uint8_t currentMode = getVirtualBoxMode(index);
    uint8_t newMode = currentMode;
    do
    {
        newMode = random(FX_MODE_CUSTOM + 1);
    } while (currentMode == newMode);
    setVirtualBoxMode(index, newMode, newSpeed);
    return currentMode;
};

uint8_t ConnectVirtualBox::previousVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{
    int8_t currentMode = getVirtualBoxMode(index);
    currentMode--;
    if (currentMode <= 0)
        currentMode = FX_MODE_CUSTOM - 1;
    setVirtualBoxMode(index, currentMode, newSpeed);
    return currentMode;
};

uint32_t* ConnectVirtualBox::setVirtualBoxColor(uint8_t indexLayer, uint8_t indexColor, uint32_t color)
{
    VirtualBox *layer = virtualBoxes[indexLayer];
    uint32_t* ret = new uint32_t[MAX_NUM_COLORS]();
    for (size_t i = 0; i < MAX_NUM_COLORS; i++)
    {
        layer->setColorByIndex(i, listColors[indexColor][i]);
        ret[i] = listColors[indexColor][i];
    }
    return ret;
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
    vocaStatus.waitStatus(Status_Store_Initialized);
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->init();
        virtualBoxes[i]->setBrightness(255);
        virtualBoxes[i]->start();
    }
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tmp;
        tmp = String("enLyr_") + i;
        if (vocaStore.getValue(tmp, "true", true, false) == "true")
        {
            virtualBoxes[i]->enable();
        }
        else
        {
            virtualBoxes[i]->disable();
        }

        splitSegment(virtualBoxes[i]);

        for (size_t mi = 0; mi < virtualBoxes[i]->getModeCount(); mi++)
        {
            String spdKey = "spdLyr_";
            spdKey += String(i) + "_";
            spdKey += String(mi);
            virtualBoxes[i]->setSpeedForMode(mi, vocaStore.getValue(spdKey, String(mapSpeedDefault[mi]), true, false).toInt());
        }

        tmp = String("mdLyr_") + i;
        uint8_t currentMode = vocaStore.getValue(tmp, "2", true, false).toInt();
        uint16_t newSpeed;
        setVirtualBoxMode(i, currentMode, &newSpeed);
        setVirtualBoxSpeed(i, newSpeed);

        tmp = String("cl0Lyr_") + i;
        uint32_t color;
        color = stringToColor(vocaStore.getValue(tmp, "#ff0000", true, false));
        setVirtualBoxColor(i, 0, color);

        tmp = String("cl1Lyr_") + i;
        color = stringToColor(vocaStore.getValue(tmp, "#00ff00", true, false));
        setVirtualBoxColor(i, 1, color);

        tmp = String("cl2Lyr_") + i;
        color = stringToColor(vocaStore.getValue(tmp, "#0000ff", true, false));
        setVirtualBoxColor(i, 1, color);

        tmp = String("brgLyr_") + i;
        setVirtualBoxBrightness(i, vocaStore.getValue(tmp, "50", true, false).toInt());
    }
    vocaStore.updateStore();
};
void ConnectVirtualBox::beginVirtualBoxes()
{

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i] = new VirtualBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    }
};

ConnectVirtualBox::~ConnectVirtualBox()
{
}
