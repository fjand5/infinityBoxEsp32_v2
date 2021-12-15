#include "box/box.h"
#include "voca_render.h"

void setup_render_layer()
{
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;
        renderSwitch(tab_name, String("en_layer_") + i, R"({
    "name":"Bật",
    "description":"",
    "newLine":true,      
  })",
                     [](String key, String value)
                     {
                         setValue(key, value);
                     });
    }
};