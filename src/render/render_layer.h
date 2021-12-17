#include "box/box_controler.h"
#include "voca_render.h"
void setup_render_layer()
{
    xEventGroupWaitBits(box_status, FLAG_BOX_READY, pdFALSE, pdFALSE, portMAX_DELAY);
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        String tmp;
        tmp = String("en_layer_") + i;
        if (getValue(tmp, "true") == "true")
        {
            log_i("cmd: %s", tmp.c_str());
            box_enable(i);
        }
        else
        {
            log_i("cmd: %s", tmp.c_str());
            box_disable(i);
        }
        renderSwitch(tab_name, String("en_layer_") + i, R"({
    "name":"Chạy",
  })",
                     [](String key, String value)
                     {
                         int li;
                         key.replace("en_layer_", "");
                         li = key.toInt();
                         if (value == "true")
                             box_enable(li);
                         else
                             box_disable(li);
                     });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        String tmp;
        tmp = String("color0_layer_") + i;
        renderColorPicker(tab_name, String("color0_layer_") + i, R"({
    "name":"Màu 0",
  })",
                     [](String key, String value)
                     {
                         int li;
                         key.replace("color0_layer_", "");
                         li = key.toInt();
                         if (value == "true")
                             box_enable(li);
                         else
                             box_disable(li);
                     });
    };

};