#pragma once
#include "box/box_controller.h"
#include "box/box_env.h"

#include "voca_render/voca_render.h"
#include "../controller.h"

void setup_render_layer()
{
    for (int i = 0; i < NUM_OF_LAYER; i++)
    {
        String tab_name;
        tab_name = String("Layer ") + i;
        int *index = new int(i);

        vocaRender.renderSwitch(
            tab_name, String("enLyr_") + i,
            F(R"({
                    "name":"Chạy",
                    "newLine":true
                })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                if (value == "true")
                    box_enable(li);
                else
                    box_disable(li);
            },
            (void *)index);

        vocaRender.renderSwitch(
            tab_name, String("rdmTmrMd"),
            F(R"({
                    "name":"Timer Mode",
                    "newLine":true
                })"),
            [](String key, String value, void *param)
            {
                if (value == "true")
                {
                    onTimerMode();
                }
                else
                {
                    offTimerMode();
                }
            },
            (void *)index);

        vocaRender.renderSwitch(
            tab_name, String("msMd"),
            F(R"({
                    "name":"Music Mode",
                    "newLine":true
                })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);

                if (value == "true")
                {
                    box_setMusicMode(li, true);
                }
                else
                {
                    box_setMusicMode(li, false);
                }
            },
            (void *)index);
        vocaRender.renderButton(
            tab_name, String("save_layer_") + i,
            F(R"({
                    "name":"Lưu",
                    "newLine":true
                })"),
            [](String key, String value, void *param)
            {
                vocaStore.updateStore();
            },
            NULL);
        vocaRender.renderSlider(
            tab_name, String("brgLyr_") + i,
            F(R"({
                    "name":"Độ sáng",
                    "min":0,
                    "max":255,
                    "newLine":true
                })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                box_setBrightness(li, value.toInt());
            },
            (void *)index);

        vocaRender.renderSelect(
            tab_name, String("clLyr_") + i,
            F(R"({
                    "name":"Mẫu màu",
                    "options":[
                    "00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15"],
                    "span":{
                        "xs":24,
                        "sm":24,
                        "md":12,
                        "xl":12
                    },
                    "newLine":true
                })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                box_setColor(li, value.toInt());
            },
            (void *)index);

        vocaRender.renderColorPicker(
            tab_name, String("cl0Lyr_") + i, F(R"({
            "name":"Màu 0"
          })"),
            [](String key, String value, void *param) {
            },
            NULL);
        vocaRender.renderColorPicker(
            tab_name, String("cl1Lyr_") + i, F(R"({
            "name":"Màu 1"
          })"),
            [](String key, String value, void *param) {
            },
            NULL);
        vocaRender.renderColorPicker(
            tab_name, String("cl2Lyr_") + i, F(R"({
            "name":"Màu 2",
            "newLine":true
          })"),
            [](String key, String value, void *param) {
            },
            NULL);

        vocaRender.renderButton(
            tab_name, String("mdLyr_") + i + "_prv", F(R"({
    "name":"Prev"
  })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                box_prevMode(li);
            },
            (void *)index);

        vocaRender.renderButton(
            tab_name, String("mdLyr_") + i + "_rnd", F(R"({
    "name":"Random",
    "newLine":true
  })"),
            [](String key, String value, void *param)
            {
                box_randomModeAll();
            },
            NULL);
        vocaRender.renderButton(
            tab_name, String("mdLyr_") + i + "_nxt", F(R"({
    "name":"Next",
    "newLine":true
  })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                box_nextMode(li);
            },
            (void *)index);

        vocaRender.renderSelect(
            tab_name, String("mdLyr_") + i, F(R"({
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
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                box_setMode(li, value.toInt());
            },
            (void *)index);

        vocaRender.renderInput(
            tab_name, String("spdLyr_") + i, F(R"({
    "name":"Tốc độ",
    "newLine":true
  })"),
            [](String key, String value, void *param)
            {
                int li = *((int *)param);
                box_setSpeed(li, value.toInt());
            },
            (void *)index);
    };
};