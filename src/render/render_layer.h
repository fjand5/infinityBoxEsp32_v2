#include "box/box_controler.h"
#include "voca_render.h"
void setup_render_layer()
{
    xEventGroupWaitBits(box_status, FLAG_BOX_READY, pdFALSE, pdFALSE, portMAX_DELAY);
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        renderSwitch(tab_name, String("en_layer_") + i, R"({
    "name":"Chạy",
    "newLine":true
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
        renderSlider(tab_name, String("brig_layer_") + i, R"({
    "name":"Độ sáng",
    "min":0,
    "max":255,
    "newLine":true
  })",
                     [](String key, String value)
                     {
                         int li;
                         key.replace("brig_layer_", "");
                         li = key.toInt();
                         box_setBrightness(li, value.toInt());
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
                              box_setColor(li, 0, value);
                          });

        tmp = String("color1_layer_") + i;
        renderColorPicker(tab_name, String("color1_layer_") + i, R"({
    "name":"Màu 1",
  })",
                          [](String key, String value)
                          {
                              int li;
                              key.replace("color1_layer_", "");
                              li = key.toInt();
                              box_setColor(li, 1, value);
                          });

        tmp = String("color2_layer_") + i;
        renderColorPicker(tab_name, String("color2_layer_") + i, R"({
    "name":"Màu 2",
    "newLine":true
  })",
                          [](String key, String value)
                          {
                              int li;
                              key.replace("color2_layer_", "");
                              li = key.toInt();
                              box_setColor(li, 2, value);
                          });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        String tmp;
        tmp = String("mode_layer_") + i;
        renderSelect(tab_name, String("mode_layer_") + i, R"({
    "name":"Hiệu ứng",
    "options":["0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19"],
  })",
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mode_layer_", "");
                         li = key.toInt();
                         box_setMode(li, value.toInt());
                     });
    };
};