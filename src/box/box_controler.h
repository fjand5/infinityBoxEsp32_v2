#pragma once
#include "box.h"
#include "voca_core.h"
extern VBox layers[];
extern SemaphoreHandle_t control_layer_sem;

void box_pause(int8_t layer)
{
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {
        BaseType_t xReturned = xTaskCreatePinnedToCore(
            [](void *params)
            {
                VBox* _layer = (VBox*)params;
                _layer->pause();
                vTaskDelete(NULL);
            },                        /* Task function. */
            "box_pause",              /* name of task. */
            2048,                    /* Stack size of task */
            (void *)&layers[layer],            /* parameter of the task */
            1, /* priority of the task */
            NULL,                     /* Task handle to keep track of created task */
            BOX_CORE_CPU);            /* pin task to core 0 */
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("en_layer_") + layer, "false", false);
        }
    }
}
void box_resume(int8_t layer)
{
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {

        BaseType_t xReturned = xTaskCreatePinnedToCore(
            [](void *params)
            {
                VBox* _layer = (VBox*)params;
                _layer->resume();
                vTaskDelete(NULL);
            },                        /* Task function. */
            "box_resume",             /* name of task. */
            2048,                    /* Stack size of task */
            (void *)&layers[layer],            /* parameter of the task */
            1, /* priority of the task */
            NULL,                     /* Task handle to keep track of created task */
            BOX_CORE_CPU);            /* pin task to core 0 */
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("en_layer_") + layer, "true", false);
        }
    }
}