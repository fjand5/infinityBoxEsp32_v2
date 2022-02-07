#include "real_box.h"

static VirtualBox *virtualBoxes[NUM_OF_LAYER];
RealBox realBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
RealBox::RealBox(uint16_t num_leds, uint8_t pin, neoPixelType type) : WS2812FX(num_leds, pin, type)
{
}

void IRAM_ATTR RealBox::boxShow()
{
    for (uint16_t i = 0; i < realBox.getNumBytes(); i++)
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
            realBox.getPixels()[i] = sumPixelsValue / count;
        else
            realBox.getPixels()[i] = 0;
    }
    rmt_write_sample(RMT_CHANNEL, realBox.getPixels(), realBox.getNumBytes(), false); // channel 0
}
void RealBox::boxHandle()
{
    log_w("Box is running on core: %d", xPortGetCoreID());
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->init();
        virtualBoxes[i]->setBrightness(255);
        virtualBoxes[i]->start();
    }

    init();
    rmt_tx_int(RMT_CHANNEL, getPin());
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i]->setCustomShow(boxShow);
    }
    // init_virtualBoxes(virtualBoxes);
    xEventGroupSetBits(box_status, FLAG_BOX_READY);
    queueCommand = xQueueCreate(NUM_OF_COMMAND_WAITING, sizeof(RealBoxCommandBundle));
    // boxCommandResoponseQueue = xQueueCreate(1, sizeof(BoxCommand));
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
        // command_handle(virtualBoxes);
        for (size_t i = 0; i < NUM_OF_LAYER; i++)
        {
            virtualBoxes[i]->service();
        }
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

void RealBox::feedCommand(RealBoxCommandBundle realBoxCommandBundle, ResponseCommand cbResponseCommand)
{
    uint32_t id = millis();
    realBoxCommandBundle.id = id;
    responseCommandIndex.insert(std::pair<uint32_t, ResponseCommand>(id, cbResponseCommand));
    xQueueSend(queueCommand, (void *)&realBoxCommandBundle, portMAX_DELAY);
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
    RealBoxCommandBundle rxBoxCmd;

    if (checkCommand(&rxBoxCmd))
    {
        if (rxBoxCmd.cmd == BOX_CONFIG_SEGMENT)
        {
            uint16_t num = *((uint16_t *)rxBoxCmd.p);
            bool rev = rxBoxCmd.option;
            for (uint8_t i = 0; i < NUM_OF_LAYER; i++)
            {
                virtualBoxes[i]->resetSegments();
                virtualBoxes[i]->clear();
                virtualBoxes[i]->setSegment(0,
                                     LED_COUNT_ONE_SEG * num,
                                     LED_COUNT_ONE_SEG * (num + 1) - 1,
                                     FX_MODE_COLOR_WIPE, DEFAULT_COLOR, DEFAULT_SPEED, rev);
                virtualBoxes[i]->setConfigState(true);
            }
            responseResult(rxBoxCmd);
        }
        else if (rxBoxCmd.cmd == BOX_CONFIG_SHOW_FACE)
        {
            Face face = *((Face *)rxBoxCmd.p);
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
                virtualBoxes[i]->setConfigState(true);
            }
            responseResult(rxBoxCmd);
        }
        else
        {
            if (virtualBoxes[rxBoxCmd.layer]->getConfigState() == true)
            {
                virtualBoxes[rxBoxCmd.layer]->setConfigState(false);
                // init_layers(*virtualBoxes);
            }

            if (rxBoxCmd.cmd == BOX_ENABLE)
            {

                virtualBoxes[rxBoxCmd.layer]->enable();
                responseResult(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_DISABLE)
            {
                virtualBoxes[rxBoxCmd.layer]->disable();
                responseResult(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_GET_MODE)
            {
                uint8_t modeInt = virtualBoxes[rxBoxCmd.layer]->getMode();
                RealBoxCommandBundle res;
                res.id = rxBoxCmd.id;
                res.p = &modeInt;
                responseResult(res);
            }
            else if (rxBoxCmd.cmd == BOX_SET_MODE)
            {
                char *modeStr = (char *)rxBoxCmd.p;
                uint8_t modeInt = virtualBoxes[rxBoxCmd.layer]->getNumModeName(String(modeStr));
                struct SetModeBundle
                {
                    VirtualBox *layers;
                    uint8_t index;
                    uint8_t mode;
                    uint16_t speed;
                } setModeBundle;
                setModeBundle.layers = *virtualBoxes;
                setModeBundle.index = rxBoxCmd.layer;
                setModeBundle.mode = modeInt;
                setModeBundle.speed = rxBoxCmd.option;
                // BOX_THREAD([](void *p)
                //            {
                //                SetModeBundle setModeBundle = *((SetModeBundle *)p);
                //                uint8_t numOfSegment = setModeBundle.layers[setModeBundle.index].getNumSegments();
                //                for (int i = 0; i < numOfSegment; i++)
                //                {
                //                    setModeBundle.layers[setModeBundle.index].setMode(i, setModeBundle.mode);
                //                    setModeBundle.layers[setModeBundle.index].setSpeed(i, setModeBundle.speed);

                //                    delay(TRANSITION_TIME / numOfSegment);
                //                };
                //                vTaskDelete(NULL); },
                //            &setModeBundle);
                responseResult(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_SET_COLOR)
            {
                virtualBoxes[rxBoxCmd.layer]->setColorByIndex(rxBoxCmd.option, *((uint32_t *)rxBoxCmd.p));
                responseResult(rxBoxCmd);
            }
            else if (rxBoxCmd.cmd == BOX_SET_BRIGHTNESS)
            {
                virtualBoxes[rxBoxCmd.layer]->setBrightness(*((uint8_t *)rxBoxCmd.p));
                responseResult(rxBoxCmd);
            }

            else if (rxBoxCmd.cmd == BOX_SET_SPEED)
            {
                // setLayerSpeed(virtualBoxes[rxBoxCmd.layer],*((uint16_t *)rxBoxCmd.p));
                responseResult(rxBoxCmd);
            }
            else
            {
                responseResult(rxBoxCmd);
            }
        }
    }
}
void RealBox::begin()
{
    BaseType_t xReturned;
    log_w("setup_box starting: %d", xPortGetCoreID());

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        virtualBoxes[i] = new VirtualBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
    }
    // vocaStatus.waitStatus(Status_Store_Initialized);

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
