#pragma once
#define NUM_OF_LAYER 3
#include "p_box.h"
#include "v_box.h"
VBox layers[NUM_OF_LAYER] = {VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800),VBox(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800)};

void boxHandle(void *params)
{
    // Box.addVBox(layer1);
    log_w("boxHandle is running on core: %d", xPortGetCoreID());
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        Box.addVBox(layers[i]);
    }
    
    Box.setup();
    layers[0].setMode(FX_MODE_COLOR_WIPE);
    layers[0].setColor(GREEN);
    // layer1.setMode(FX_MODE_RUNNING_RANDOM);
    layers[1].setMode(FX_MODE_FADE);
    layers[1].setSpeed(300);

    while (1)
    {
        Box.service_handle();
        delay(10);
    }
}
void setup_box()
{
    BaseType_t xReturned;
    log_w("setup_box starting: %d", xPortGetCoreID());

    xReturned = xTaskCreatePinnedToCore(
        boxHandle,            /* Task function. */
        "boxHandle",          /* name of task. */
        10000,                /* Stack size of task */
        NULL,                 /* parameter of the task */
        configMAX_PRIORITIES, /* priority of the task */
        NULL,                 /* Task handle to keep track of created task */
        0);                   /* pin task to core 0 */
    if (xReturned == pdPASS)
    {
        /* The task was created.  Use the task's handle to delete the task. */
        log_w("setup_box created: %d", xPortGetCoreID());

    }else{
         log_w("setup_box create faile: %d", xPortGetCoreID());
    }
}