#include "real_box.h"
RealBox realBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

RealBox::RealBox(uint16_t num_leds, uint8_t pin, neoPixelType type) : WS2812FX(num_leds, pin, type)
{
}

void IRAM_ATTR RealBox::boxShow()
{
    mixVirtualBox(realBox.getPixels(), realBox.getNumBytes());
    rmt_write_sample(RMT_CHANNEL, realBox.getPixels(), realBox.getNumBytes(), false); // channel 0
}
void RealBox::boxHandle()
{
    log_w("Box is running on core: %d", xPortGetCoreID());
    queueCommand = xQueueCreate(NUM_OF_COMMAND_WAITING, sizeof(RealBoxCommandBundle));
    init();
    rmt_tx_int(RMT_CHANNEL, getPin());
    setVirtualBoxesDisplay(boxShow);
    initVirtualBoxes();
    log_w("Box has initialze !!!");

    while (1)
    {
        // static UBaseType_t lastUxHighWaterMark = 0;
        // UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        // if (lastUxHighWaterMark != uxHighWaterMark)
        // {
        //     lastUxHighWaterMark = uxHighWaterMark;
        //     log_w("uxTaskGetStackHighWaterMark: %d", lastUxHighWaterMark);
        // }
        microphone.handleMicrophone(
            [](void *param, double val, double freq)
            {
                RealBox *realBox = (RealBox *)param;
                realBox->onBeatVirtualBoxes(val, freq);
            },
            this);
        commandHandle();
        serviceVirtualBoxes();
    }
}
void RealBox::feedCommand(RealBoxCommandBundle *realBoxCommandBundle, ResponseCommand cbResponseCommand)
{
    uint32_t id = micros();
    realBoxCommandBundle->id = id;
    responseCommandIndex[id] = cbResponseCommand;
    xQueueSend(queueCommand, (void *)realBoxCommandBundle, portMAX_DELAY);
};

uint8_t RealBox::getModeNum(String mode)
{
    for (size_t i = 0; i < getModeCount(); i++)
    {
        if (mode == getModeName(i))
        {
            return i;
        }
    }
    return 0;
};
void RealBox::responseResult(RealBoxCommandBundle realBoxCommandBundle)
{
    uint32_t id;
    for (auto r = responseCommandIndex.begin();
         r != responseCommandIndex.end();
         ++r)
    {
        id = r->first;
        if (realBoxCommandBundle.id == id)
        {
            r->second(realBoxCommandBundle);
            break;
        }
    }
    responseCommandIndex.erase(id);
};

BaseType_t RealBox::checkCommand(RealBoxCommandBundle *realBoxCommandBundle)
{

    return xQueueReceive(queueCommand,
                         realBoxCommandBundle, 0);
};
void RealBox::commandHandle()
{
    if (checkCommand(&commandInfo) == pdTRUE)
    {
        if (commandInfo.cmd == BoxCommand_ConfigSegment)
        {
            configSegment(commandInfo.numSeg, commandInfo.rev);
            responseResult(commandInfo);
        }
        else if (commandInfo.cmd == BoxCommand_ConfigShowFace)
        {
            Face face = *((Face *)commandInfo.p);
            configShowFace(face);
            responseResult(commandInfo);
        }
        else
        {
            if (getConfigState() == true)
            {
                setConfigState(false);
                initVirtualBoxes();
            }

            if (commandInfo.cmd == BoxCommand_Enable)
            {
                enableVirtualBox(commandInfo.layer);
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BoxCommand_Disable)
            {
                disableVirtualBox(commandInfo.layer);
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BoxCommand_GetMode)
            {
                uint8_t modeInt = getVirtualBoxMode(commandInfo.layer);
                RealBoxCommandBundle res;
                res.id = commandInfo.id;
                res.mode = modeInt;
                responseResult(res);
            }
            else if (commandInfo.cmd == BoxCommand_SetMode)
            {
                uint16_t newSpeed;
                setVirtualBoxMode(commandInfo.layer, commandInfo.mode, &newSpeed);
                commandInfo.speed = newSpeed;
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BoxCommand_RandomMode)
            {
                uint16_t newSpeed;
                uint8_t newMode = randomVirtualBoxMode(commandInfo.layer, &newSpeed);
                commandInfo.speed = newSpeed;
                commandInfo.mode = newMode;
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BoxCommand_NextMode)
            {
                uint16_t newSpeed;
                uint8_t newMode = nextVirtualBoxMode(commandInfo.layer, &newSpeed);
                commandInfo.speed = newSpeed;
                commandInfo.mode = newMode;
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BoxCommand_PreviousMode)
            {
                uint16_t newSpeed;
                uint8_t newMode = previousVirtualBoxMode(commandInfo.layer, &newSpeed);
                commandInfo.speed = newSpeed;
                commandInfo.mode = newMode;
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BoxCommand_SetColor)
            {
                uint32_t *colors = new uint32_t[MAX_NUM_COLORS]();
                setVirtualBoxColor(commandInfo.layer, commandInfo.colorIndex, colors);
                commandInfo.colors = colors;
                responseResult(commandInfo);
                delete colors;
            }
            else if (commandInfo.cmd == BoxCommand_SetBrightness)
            {
                setVirtualBoxBrightness(commandInfo.layer, commandInfo.brightness);
                responseResult(commandInfo);
            }

            else if (commandInfo.cmd == BoxCommand_SetSpeed)
            {
                setVirtualBoxSpeed(commandInfo.layer, commandInfo.speed);
                String tmp;
                tmp = getModeName(getMode());
                commandInfo.p = (void *)tmp.c_str();
                responseResult(commandInfo);
            }
            
            else if (commandInfo.cmd == BoxCommand_SetMusicMode)
            {
                setMusicMode(commandInfo.layer, commandInfo.musicModeState);
                responseResult(commandInfo);
            }else
            {
                responseResult(commandInfo);
            }
        }
    }
}
bool RealBox::isCustomMode(uint8_t mode)
{
    return mode >= FX_MODE_CUSTOM;
}
void RealBox::begin()
{
    BaseType_t xReturned;
    log_w("setup_box starting: %d", xPortGetCoreID());
    beginVirtualBoxes();
    box_status = xEventGroupCreate();

    xReturned = xTaskCreatePinnedToCore(
        [](void *prams)
        {
            RealBox *_realBox = (RealBox *)prams;
            _realBox->boxHandle();
        },             /* Task function. */
        "boxHandle",   /* name of task. */
        10000,          /* Stack size of task */
        (void *)this,  /* parameter of the task */
        0,             /* priority of the task */
        NULL,          /* Task handle to keep track of created task */
        BOX_CORE_CPU); /* pin task to core 0 */
}

RealBox::~RealBox()
{
}
