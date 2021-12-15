#pragma once
#include "p_box.h"
#include "v_box.h"
VBox layer1(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
VBox layer2(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
VBox layer3(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void boxHandle(void *params)
{
    // Box.addVBox(layer1);
    log_w("boxHandle is running on core: %d",xPortGetCoreID());

    Box.addVBox(layer2);
    Box.addVBox(layer3);
    Box.setup();
    layer2.setMode(FX_MODE_COLOR_WIPE);
    layer2.setColor(GREEN);
    // layer1.setMode(FX_MODE_RUNNING_RANDOM);
    layer3.setMode(FX_MODE_BLINK);
    layer3.setSpeed(300);

    while (1)
    {
        Box.service_handle();
    }
}
void setup_box()
{
    xTaskCreatePinnedToCore(
        boxHandle,            /* Task function. */
        "boxHandle",          /* name of task. */
        100000,                /* Stack size of task */
        NULL,                 /* parameter of the task */
        configMAX_PRIORITIES, /* priority of the task */
        NULL,                 /* Task handle to keep track of created task */
        1);                   /* pin task to core 0 */
}