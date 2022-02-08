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
    setDisplay(boxShow);
    // init_virtualBoxes(virtualBoxes);
    // xEventGroupSetBits(box_status, FLAG_BOX_READY);
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
        // command_handle(virtualBoxes)
        ConnectVirtualBox::service();
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
            configSegment(num, rev);
            responseResult(rxBoxCmd);
        }
        else if (rxBoxCmd.cmd == BOX_CONFIG_SHOW_FACE)
        {
            Face face = *((Face *)rxBoxCmd.p);
            configShowFace(face);
            responseResult(rxBoxCmd);
        }
        else
        {
            if (getConfigState() == true)
            {
                setConfigState(false);
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
    // vocaStatus.waitStatus(Status_Store_Initialized);
    ConnectVirtualBox::begin();
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
