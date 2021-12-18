#pragma once
#include "box.h"
#include "ultis.h"
#include "voca_core.h"
#define EXE_BOX_COMMAND(prams, cmd) xTaskCreatePinnedToCore( \
    [](void *params)                                         \
    {                                                        \
        cmd                                                  \
            vTaskDelete(NULL);                               \
    },\                     
            "box_pause",\             
            2048,\               
            (void *)prams,   \     
            1,                                               \
    NULL,\                    
            BOX_CORE_CPU);
extern VBox layers[];
extern SemaphoreHandle_t control_layer_sem;

void box_enable(int8_t layer)
{
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {
        BaseType_t xReturned = EXE_BOX_COMMAND(&layers[layer], VBox *_layer = (VBox *)params; _layer->enable(););
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

        BaseType_t xReturned = EXE_BOX_COMMAND(&layers[layer],
                                               VBox *_layer = (VBox *)params;
                                               _layer->disable(););
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("en_layer_") + layer, "false");
        }
    }
}
void box_setMode(int8_t layer, String mode)
{
    struct ModeBundle
    {
        VBox *l;
        uint32_t m;
    } modeBundle;
    modeBundle.l = &layers[layer];
    modeBundle.m = modeBundle.l->getNumModeName(mode);
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {

        BaseType_t xReturned = EXE_BOX_COMMAND(
            &modeBundle,
            ModeBundle *modeBundle = (ModeBundle *)params;
            VBox *_l = modeBundle->l;
            for (int i = 0; i < _l->getNumSegments(); i++) {
                _l->setMode(i, modeBundle->m);
            });
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("mode_layer_") + layer, String(mode));
        }
    }
}

void box_nextMode(){
   VBox _l = layers[0];
   
   uint8_t _m = _l.getMode();
   uint8_t _nm = _m++;
   if(_nm >= MODE_COUNT){
       _nm = 0;
   }
//    box_setMode(0,_m);
}
void box_setColor(int8_t layer, int8_t iColor, String color)
{
    struct ColorBundle
    {
        VBox *l;
        int8_t i;
        uint32_t c;
    } colorBundle;
    colorBundle.l = &layers[layer];
    colorBundle.i = iColor;
    colorBundle.c = stringToColor(color);
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {

        BaseType_t xReturned = EXE_BOX_COMMAND(&colorBundle,

                                               ColorBundle *colorBundle = (ColorBundle *)params;
                                               (colorBundle->l)->setColorByIndex(colorBundle->i, colorBundle->c);

        );
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("color") + iColor + "_layer_" + layer, color);
        }
    }
}

void box_setBrightness(int8_t layer, uint8_t brightness)
{
    struct BrightnessBundle
    {
        VBox *l;
        uint32_t b;
    } brightnessBundle;
    brightnessBundle.l = &layers[layer];
    brightnessBundle.b = brightness;
    if (xSemaphoreTake(control_layer_sem, portMAX_DELAY) == pdTRUE)
    {

        BaseType_t xReturned = EXE_BOX_COMMAND(&brightnessBundle,

                                               BrightnessBundle *brightnessBundle = (BrightnessBundle *)params;
                                               (brightnessBundle->l)->setBrightness(brightnessBundle->b);

        );
        xSemaphoreGive(control_layer_sem);
        if (xReturned == pdPASS)
        {
            setValue(String("brig_layer_") + layer, String(brightness));
        }
    }
}