#pragma once
#include "box/box_controler.h"
#include "box/box_env.h"

#include "voca_render/voca_render.h"

void setup_render_layer()
{
    // if (box_status == NULL)
    // {
    //     return;
    // }

    // xEventGroupWaitBits(box_status, FLAG_BOX_READY, pdFALSE, pdFALSE, portMAX_DELAY);

    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;

        vocaRender.renderSwitch(tab_name, String("enLyr_") + i, F(R"({
    "name":"Chạy"
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("enLyr_", "");
                         li = key.toInt();
                         if (value == "true")
                             box_enable(li);
                         else
                             box_disable(li);
                     });
        vocaRender.renderButton(tab_name, String("save_layer_") + i, F(R"({
    "name":"Lưu",
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         vocaStore.updateStore();
                     });
        vocaRender.renderSlider(tab_name, String("brgLyr_") + i, F(R"({
    "name":"Độ sáng",
    "min":0,
    "max":255,
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("brgLyr_", "");
                         li = key.toInt();
                         box_setBrightness(li, value.toInt());
                     });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;
        vocaRender.renderColorPicker(tab_name, String("cl0Lyr_") + i, F(R"({
    "name":"Màu 0"
  })"),
                          [](String key, String value)
                          {
                              int li;
                              key.replace("cl0Lyr_", "");
                              li = key.toInt();
                              box_setColor(li, 0, value);
                          });
        vocaRender.renderColorPicker(tab_name, String("cl1Lyr_") + i, F(R"({
    "name":"Màu 1"
  })"),
                          [](String key, String value)
                          {
                              int li;
                              key.replace("cl1Lyr_", "");
                              li = key.toInt();
                              box_setColor(li, 1, value);
                          });
        vocaRender.renderColorPicker(tab_name, String("cl2Lyr_") + i, F(R"({
    "name":"Màu 2",
    "newLine":true
  })"),
                          [](String key, String value)
                          {
                              int li;
                              key.replace("cl2Lyr_", "");
                              li = key.toInt();
                              box_setColor(li, 2, value);
                          });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;
        vocaRender.renderButton(tab_name, String("mdLyr_") + i + "_prv", F(R"({
    "name":"Prev"
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mdLyr_", "");
                         key.replace("_prv", "");
                         li = key.toInt();
                         box_prevMode(li);
                     });
        vocaRender.renderButton(tab_name, String("mdLyr_") + i + "_nxt", F(R"({
    "name":"Next",
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mdLyr_", "");
                         key.replace("_nxt", "");
                         li = key.toInt();
                         box_nextMode(li);
                     });

        vocaRender.renderSelect(tab_name, String("mdLyr_") + i, F(R"({
    "name":"Hiệu ứng",
    "options":[
    "00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20",
    "21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40",
    "41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60",
    "61","62","63","64"],
    "span":{
        "xs":24,
        "sm":24,
        "md":12,
        "xl":12
    },
    "newLine":true
  })"),
                     [](String key, String value)
                     {
                         int li;
                         key.replace("mdLyr_", "");
                         li = key.toInt();
                         box_setMode(li, value.toInt());
                     });
    };
    for (size_t i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;
        vocaRender.renderInput(tab_name, String("spdLyr_") + i, F(R"({
    "name":"Tốc độ",
    "newLine":true
  })"),
                    [](String key, String value)
                    {
                        int li;
                        key.replace("spdLyr_", "");
                        li = key.toInt();
                        box_setSpeed(li, value.toInt());
                    });
    };
};