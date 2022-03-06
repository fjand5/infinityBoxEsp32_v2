#include "connect_virtual_box.h"

#include "Arduino.h"

bool _isMusicMode = false;
static VirtualBox *virtualBoxes[NUM_OF_LAYER];

void ConnectVirtualBox::mixVirtualBox(uint8_t *pPixels, const uint16_t numBytes)
{
    bool hasMusicPixel = false;
    static float musicFactor = 1;
    musicFactor = musicFactor * 0.9;
    for (uint16_t i = 0; i < numBytes; i++)
    {
        uint32_t sumPixelsValue = 0;
        uint8_t count = 0;
        if (_isMusicMode)
        {
            hasMusicPixel = virtualBoxes[0]->getPixels()[i];
            if (hasMusicPixel)
            {
                musicFactor = 1000;
                memcpy(pPixels, virtualBoxes[0]->getPixels(), numBytes);
                break;
            }
        }
        for (size_t li = 0; li < NUM_OF_LAYER; li++)
        {
            if (virtualBoxes[li]->isRunning())
            {
                count++;
                sumPixelsValue += virtualBoxes[li]->getPixels()[i];
            }
        }
        if (count != 0)
        {

            pPixels[i] = sumPixelsValue / (count + musicFactor);
        }
        else
            pPixels[i] = 0;
    }
}
ConnectVirtualBox::ConnectVirtualBox(/* args */)
{
    Sem_WaitSetModeFinish = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_WaitSetModeFinish);
}

void ConnectVirtualBox::configSegment(uint16_t num, bool rev)
{
    setConfigState(true);
    setMusicMode(false);
    for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->controlVirtualBox(
            [num, rev](void *virtualBox, void *param)
            {
                VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
                _virtualBox->resetSegments();
                _virtualBox->clear();
                _virtualBox->setSegment(0,
                                        LED_COUNT_ONE_SEG * num,
                                        LED_COUNT_ONE_SEG * (num + 1) - 1,
                                        FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, rev);
                _virtualBox->setBrightness(255);
            },
            NULL);
    }
};

void ConnectVirtualBox::configShowFace(Face face)
{
    setConfigState(true);
    setMusicMode(false);

    for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->controlVirtualBox(
            [face](void *virtualBox, void *param)
            {
                VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
                _virtualBox->resetSegments();
                _virtualBox->clear();
                _virtualBox->setSegment(0,
                                        LED_COUNT_ONE_SEG * face.start1,
                                        LED_COUNT_ONE_SEG * (face.start1 + 1) - 1,
                                        FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv1);
                _virtualBox->setSegment(1,
                                        LED_COUNT_ONE_SEG * face.start2,
                                        LED_COUNT_ONE_SEG * (face.start2 + 1) - 1,
                                        FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv2);
                _virtualBox->setSegment(2,
                                        LED_COUNT_ONE_SEG * face.start3,
                                        LED_COUNT_ONE_SEG * (face.start3 + 1) - 1,
                                        FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv3);
                _virtualBox->setSegment(3,
                                        LED_COUNT_ONE_SEG * face.start4,
                                        LED_COUNT_ONE_SEG * (face.start4 + 1) - 1,
                                        FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, face.inv4);
            },
            NULL);
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

        std::string value;

        value = vocaStore.getValue("sg_ft_1", "15");
        tmp = atoi(value.c_str());
        value = vocaStore.getValue("sg_ft_1_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;
        value = vocaStore.getValue("sg_tp_4", "16");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_tp_4_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_ft_2", "14");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_ft_2_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_lf_2", "1");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_lf_2_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_ft_3", "13");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_ft_3_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bt_3", "9");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bt_3_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        // return;
        value = vocaStore.getValue("sg_ft_4", "12");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_ft_4_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_rg_1", "23");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_rg_1_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bk_1", "4");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bk_1_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_lf_4", "3");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_lf_4_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bk_2", "5");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bk_2_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_tp_2", "18");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_tp_2_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bk_3", "6");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bk_3_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_rg_3", "21");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_rg_3_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bk_4", "7");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bk_4_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bt_1", "11");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bt_1_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_tp_3", "17");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_tp_3_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_lf_3", "2");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_lf_3_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_tp_1", "19");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_tp_1_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_rg_4", "20");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_rg_4_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bt_4", "8");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bt_4_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_lf_1", "0");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_lf_1_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_bt_2", "10");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_bt_2_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
        index++;

        value = vocaStore.getValue("sg_rg_2", "22");
        tmp = atoi(value.c_str());

        value = vocaStore.getValue("sg_rg_2_rv", "true");
        opt = !value.compare("true");
        opt = opt << 7;
        layer->setSegment(index, LED_COUNT_ONE_SEG * tmp + offset, LED_COUNT_ONE_SEG * (tmp + 1) - 1 + offset, mode, color, speed,
                          opt);
    }
}

void ConnectVirtualBox::enableVirtualBox(uint8_t index)
{
    virtualBoxes[index]->controlVirtualBox(
        [](void *virtualBox, void *param)
        {
            VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
            _virtualBox->enable();
        },
        NULL);
};

void ConnectVirtualBox::disableVirtualBox(uint8_t index)
{
    virtualBoxes[index]->controlVirtualBox(
        [](void *virtualBox, void *param)
        {
            VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
            _virtualBox->disable();
        },
        NULL);
};

uint8_t ConnectVirtualBox::getVirtualBoxMode(uint8_t index)
{
    uint8_t ret;
    virtualBoxes[index]->controlVirtualBox(
        [&ret](void *virtualBox, void *param)
        {
            VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
            ret = _virtualBox->getMode();
        },
        NULL);
    return ret;
};

void ConnectVirtualBox::setVirtualBoxMode(uint8_t index, uint8_t mode, uint16_t *newSpeed, bool wait)
{

    // Không cho điều khiển mode ở layer0 trong chế độ music
    if (index == 0 && _isMusicMode == true)
    {
        return;
    }
    struct SetModeBundle
    {
        VirtualBox *layer;
        uint8_t index;
        uint8_t mode;
        SemaphoreHandle_t sem;
    };
    SetModeBundle *setModeBundle = new SetModeBundle;
    setModeBundle->layer = virtualBoxes[index];
    setModeBundle->index = index;
    setModeBundle->mode = mode;
    setModeBundle->sem = Sem_WaitSetModeFinish;
    if (newSpeed != NULL)
    {
        virtualBoxes[index]->controlVirtualBox(
            [newSpeed, setModeBundle](void *virtualBox, void *param)
            {
                VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
                *newSpeed = _virtualBox->getSpeedByMode(setModeBundle->mode);
            },
            NULL);
    }

    xSemaphoreTake(Sem_WaitSetModeFinish, portMAX_DELAY);
    xTaskCreatePinnedToCore(
        [](void *p)
        {
            SetModeBundle *setModeBundle = (SetModeBundle *)p;
            VirtualBox *virtualBox = setModeBundle->layer;
            uint8_t numOfSegment;
            virtualBox->controlVirtualBox(
                [&numOfSegment](void *virtualBox, void *param)
                {
                    VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
                    numOfSegment = _virtualBox->getNumSegments();
                },
                NULL);
            for (int i = 0; i < numOfSegment; i++)
            {

                virtualBox->controlVirtualBox(
                    [&numOfSegment, i, setModeBundle](void *virtualBox, void *param)
                    {
                        VirtualBox *_virtualBox = (VirtualBox *)virtualBox;

                        uint16_t _newSpeed = _virtualBox->getSpeedByMode(setModeBundle->mode);
                        _virtualBox->setMode(i, setModeBundle->mode);
                        _virtualBox->setSpeed(i, _newSpeed);
                    },
                    NULL);

                delay(TRANSITION_TIME / numOfSegment);
            };
            delete setModeBundle;

            xSemaphoreGive(setModeBundle->sem);

            vTaskDelete(NULL);
        },
        "setVirtualBoxMode",
        4096,
        (void *)setModeBundle,
        0,
        NULL,
        BOX_CORE_CPU);
    if (wait)
    {
        xSemaphoreTake(Sem_WaitSetModeFinish, portMAX_DELAY);
    }
    xSemaphoreGive(Sem_WaitSetModeFinish);
};

uint8_t ConnectVirtualBox::nextVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{

    uint8_t currentMode = getVirtualBoxMode(index);
    currentMode++;
    if (currentMode >= FX_MODE_CUSTOM)
        currentMode = 0;
    setVirtualBoxMode(index, currentMode, newSpeed);
    return currentMode;
};
uint8_t ConnectVirtualBox::randomVirtualBoxMode(uint8_t index, uint16_t *newSpeed)
{
    uint8_t currentMode = getVirtualBoxMode(index);
    uint8_t newMode = currentMode;
    uint32_t timeout = micros();
    // Nếu trong chế độ config thì không cho phép tự chuyển mode
    if (getConfigState() == true)
        return currentMode;
    // Thời gian tối đa để chọn mode là 1ms
    do
    {
        newMode = random(FX_MODE_CUSTOM);
    } while (
        (currentMode == newMode) &&
        (micros() - timeout < 1000));
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

void ConnectVirtualBox::setVirtualBoxColor(uint8_t indexLayer, uint8_t indexColor, uint32_t *colors)
{
    VirtualBox *layer = virtualBoxes[indexLayer];

    uint32_t *_colors = new uint32_t[MAX_NUM_COLORS]();
    colorBox.readColors(indexColor, _colors);
    for (size_t i = 0; i < MAX_NUM_COLORS; i++)
    {
        layer->setColorByIndex(i, *(_colors + i));
    }
    if (colors != NULL)
    {
        memcpy(colors, _colors, MAX_NUM_COLORS * sizeof(uint32_t));
    }
    delete _colors;
};
void ConnectVirtualBox::setVirtualBoxBrightness(uint8_t index, uint8_t brightness)
{

    virtualBoxes[index]->controlVirtualBox(
        [brightness](void *virtualBox, void *param)
        {
            VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
            _virtualBox->setBrightness(brightness);
        },
        NULL);
};
void ConnectVirtualBox::setVirtualBoxSpeed(uint8_t index, uint16_t speed)
{
    virtualBoxes[index]->controlVirtualBox(
        [speed](void *virtualBox, void *param)
        {
            VirtualBox *_virtualBox = (VirtualBox *)virtualBox;

            for (int i = 0; i < _virtualBox->getNumSegments(); i++)
            {
                _virtualBox->setSpeed(i, speed);
            }
        },
        NULL);
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
void ConnectVirtualBox::onBeatVirtualBoxes(double val, double freq)
{
    if (_isMusicMode)
    {

        musicBox.onBeat(val, freq);
    }
}
void ConnectVirtualBox::setMusicMode(bool state)
{
    _isMusicMode = state;
    if (state)
    {
        virtualBoxes[0]->controlVirtualBox(
            [](void *virtualBox, void *param)
            {
                VirtualBox *_virtualBox = (VirtualBox *)virtualBox;
                for (int i = 0; i < _virtualBox->getNumSegments(); i++)
                {
                    _virtualBox->setMode(i, FX_MODE_CUSTOM_0);
                };
            },
            NULL);
    }
    else
    {
        randomVirtualBoxMode(0, NULL);
    }
};
void ConnectVirtualBox::initVirtualBoxes()
{
    vocaStatus.waitStatus(Status_Store_Initialized);
    colorBox.begin();
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->init();
        virtualBoxes[i]->setBrightness(255);
        virtualBoxes[i]->start();
    }
    for (int i = 0; i < NUM_OF_LAYER; i++)
    {
        std::string key = "enLyr_";
        key += toString(i);
        std::string value = vocaStore.getValue(key, "true", true, false);
        if (!value.compare("true"))
        {
            virtualBoxes[i]->enable();
        }
        else
        {
            virtualBoxes[i]->disable();
        }
        splitSegment(virtualBoxes[i]);

        // chỉ thiết lập với mode có sẵn, mode custom thì không đụng tới
        for (int mi = 0; mi < FX_MODE_CUSTOM; mi++)
        {
            std::string spdKey = "spdLyr_";
            spdKey += toString(i);
            spdKey += "_";
            spdKey += toString(mi);

            std::string _value = vocaStore.getValue(spdKey, toString(mapSpeedDefault[mi]), true, false);
            uint16_t speed = atoi(_value.c_str());
            virtualBoxes[i]->setSpeedForMode(mi, speed);
        }

        key = "mdLyr_";
        key += toString(i);

        value = vocaStore.getValue(key, "2", true, false);
        uint8_t currentMode = atoi(value.c_str());
        uint16_t newSpeed;
        setVirtualBoxMode(i, currentMode, &newSpeed, true);
        setVirtualBoxSpeed(i, newSpeed);

        setVirtualBoxColor(i, 0, NULL);
        setVirtualBoxColor(i, 1, NULL);
        setVirtualBoxColor(i, 2, NULL);

        key = "brgLyr_";
        key += toString(i);

        value = vocaStore.getValue(key, "50", true, false);
        setVirtualBoxBrightness(i, atoi(value.c_str()));
    }
    bool musicModeState = !vocaStore.getValue("msMd", "false", true, false).compare("true");
    setMusicMode(musicModeState);
    std::string effect = vocaStore.getValue("msEff", "0");
    musicBox.setEffect(atoi(effect.c_str()));

    vocaStore.updateStore();
};
void ConnectVirtualBox::beginVirtualBoxes()
{

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i] = new VirtualBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    }

    // Music mode chỉ chạy ở layer đầu tiên
    virtualBoxes[0]->setCustomMode(musicBox.musicEffectShow);
    musicBox.setMusicLayer(virtualBoxes[0]);
};

ConnectVirtualBox::~ConnectVirtualBox()
{
}
