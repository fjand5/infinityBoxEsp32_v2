#pragma once
#include "v_box.h"
#include "ultis.h"
#include "voca_store.h"
#include "driver_show.h"
void init_layers(VBox* layers){
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tmp;
        tmp = String("en_layer_") + i;
        if (getValue(tmp, "true") == "true")
        {
            layers[i].enable();
        }
        else
        {
            layers[i].disable();
        }

        splitSegment(&layers[i]);
        
        tmp = String("mode_layer_") + i;
        uint8_t modeInt = layers[i].getNumModeName(getValue(tmp, "1"));
        setLayerMode(&layers[i], modeInt);

        tmp = String("color0_layer_") + i;
        uint32_t color;
        color = stringToColor(getValue(tmp, "0xff0000"));
        setLayerColor(&layers[i], 0, color);

        tmp = String("color1_layer_") + i;
        color = stringToColor(getValue(tmp, "0x00ff00"));
        setLayerColor(&layers[i], 1, color);

        tmp = String("color2_layer_") + i;
        color = stringToColor(getValue(tmp, "0x0000ff"));
        setLayerColor(&layers[i], 2, color);

        tmp = String("brig_layer_") + i;
        setLayerBrightness(&layers[i], getValue(tmp, "50").toInt());
    }
}