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
    init();
    rmt_tx_int(RMT_CHANNEL, getPin());
    setVirtualBoxesDisplay(boxShow);
    initVirtualBoxes();
    queueCommand = xQueueCreate(NUM_OF_COMMAND_WAITING, sizeof(RealBoxCommandBundle));
    log_w("Box has initialze !!!");
    while (1)
    {
        static UBaseType_t lastUxHighWaterMark = 0;
        UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        if (lastUxHighWaterMark != uxHighWaterMark)
        {
            lastUxHighWaterMark = uxHighWaterMark;
            log_w("uxTaskGetStackHighWaterMark: %d", lastUxHighWaterMark);
        }
        // microphone.handleMicrophone([](double val, double freq){
        //     String tmp;
        //     for (size_t i = 0; i < val; i++)
        //     {
        //         tmp+="=";
        //     }

        //     log_w("handleMicrophone: %s", tmp.c_str());

        // });
        commandHandle();
        ConnectVirtualBox::serviceVirtualBoxes();
    }
}
void RealBox::startNextModeTimer()
{
    xTimerStart(nextModeTimer, portMAX_DELAY);
    // controlButton.setLedMode(LedMode_FadeFast);
}
void RealBox::stopNextModeTimer()
{
    xTimerStop(nextModeTimer, portMAX_DELAY);
    // controlButton.setLedMode(LedMode_Blink);
}

void RealBox::feedCommand(RealBoxCommandBundle *realBoxCommandBundle, ResponseCommand cbResponseCommand)
{
    uint32_t id = millis();
    realBoxCommandBundle->id = id;
    responseCommandIndex[id] = cbResponseCommand;
    xQueueSend(queueCommand, (void *)realBoxCommandBundle, portMAX_DELAY);
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

bool RealBox::checkCommand(RealBoxCommandBundle *realBoxCommandBundle)
{

    return xQueueReceive(queueCommand,
                         realBoxCommandBundle, 0);
};
void RealBox::commandHandle()
{
    if (checkCommand(&commandInfo))
    {
        if (commandInfo.cmd == BOX_CONFIG_SEGMENT)
        {
            uint16_t num = *((uint16_t *)commandInfo.p);
            bool rev = commandInfo.option;
            configSegment(num, rev);
            responseResult(commandInfo);
        }
        else if (commandInfo.cmd == BOX_CONFIG_SHOW_FACE)
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

            if (commandInfo.cmd == BOX_ENABLE)
            {
                enableVirtualBox(commandInfo.layer);
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BOX_DISABLE)
            {
                disableVirtualBox(commandInfo.layer);
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BOX_GET_MODE)
            {
                uint8_t modeInt = getVirtualBoxMode(commandInfo.layer);
                RealBoxCommandBundle res;
                res.id = commandInfo.id;
                res.p = &modeInt;
                responseResult(res);
            }
            else if (commandInfo.cmd == BOX_SET_MODE)
            {
                char *modeStr = (char *)commandInfo.p;
                setVirtualBoxMode(commandInfo.layer, modeStr);
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BOX_SET_COLOR)
            {
                setVirtualBoxColor(commandInfo.layer, commandInfo.option, *((uint32_t *)commandInfo.p));
                responseResult(commandInfo);
            }
            else if (commandInfo.cmd == BOX_SET_BRIGHTNESS)
            {
                setVirtualBoxBrightness(commandInfo.layer, *((uint8_t *)commandInfo.p));
                responseResult(commandInfo);
            }

            else if (commandInfo.cmd == BOX_SET_SPEED)
            {
                setVirtualBoxSpeed(commandInfo.layer, *((uint16_t *)commandInfo.p));
                responseResult(commandInfo);
            }
            else
            {
                responseResult(commandInfo);
            }
        }
    }
}
void RealBox::begin()
{
    BaseType_t xReturned;
    log_w("setup_box starting: %d", xPortGetCoreID());
    // vocaStatus.waitStatus(Status_Store_Initialized);
    beginVirtualBoxes();
    box_status = xEventGroupCreate();

    // controlButton.setClickEvent([]()
    //                             { box_nextMode(0); });
    // controlButton.setDoubleClickEvent(
    //     []()
    //     {
    //         if (xTimerIsTimerActive(nextModeTimer) == pdTRUE)
    //         {
    //             stopNextModeTimer();
    //         }
    //         else
    //         {
    //             startNextModeTimer();
    //         }
    //     });
    nextModeTimer = xTimerCreate(
        "nextModeTimer",
        5000 / portTICK_PERIOD_MS,
        pdTRUE, (void *)1,
        [](TimerHandle_t xTimer)
        {
            // box_nextMode(0);
        });
    xReturned = xTaskCreatePinnedToCore(
        [](void *prams)
        {
            RealBox *_realBox = (RealBox *)prams;
            _realBox->boxHandle();
        },             /* Task function. */
        "boxHandle",   /* name of task. */
        4096,          /* Stack size of task */
        (void *)this,  /* parameter of the task */
        0,             /* priority of the task */
        NULL,          /* Task handle to keep track of created task */
        BOX_CORE_CPU); /* pin task to core 0 */
    if (xReturned == pdPASS)
    {
        /* The task was created.  Use the task's handle to delete the task. */
        log_w("setup_box created: %d", xPortGetCoreID());
        startNextModeTimer();
    }
    else
    {
        log_w("setup_box create faile: %d", xPortGetCoreID());
    }
}

RealBox::~RealBox()
{
}
