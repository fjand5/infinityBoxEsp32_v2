#pragma once
#include "box.h"
#include "voca_core.h"
#define EXE_BOX_COMMAND(cmd) xTaskCreatePinnedToCore( \
    [](void *params)                                  \
    {                                                 \
        VBox *_layer = (VBox *)params;                \
        cmd;                                          \
        vTaskDelete(NULL);                            \
    },\                     
            "box_pause",\             
            2048,\               
            (void *)&layers[layer],   \     
            1,                                        \
    NULL,\                    
            BOX_CORE_CPU);
extern VBox layers[];
extern SemaphoreHandle_t control_layer_sem;

void box_enable(int8_t layer)
{
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {
        BaseType_t xReturned = EXE_BOX_COMMAND(_layer->enable());
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("en_layer_") + layer, "true");
        }
    }
}
void box_disable(int8_t layer)
{
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {

        BaseType_t xReturned = EXE_BOX_COMMAND(_layer->disable());
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("en_layer_") + layer, "false");
        }
    }
}

void box_setColor(int8_t layer, int8_t iColor, uint32_t color)
{
    // if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    // {

    //     BaseType_t xReturned = EXE_BOX_COMMAND(_layer->setColor(iColor, color););
    //     xSemaphoreGive(control_layer_sem);
    //     if (xReturned == pdPASS)
    //     {
    //         setValue(String("en_layer_") + layer, "false");
    //     }
    // }
}