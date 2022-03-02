#pragma once
#include "box/box_controller.h"
#include "box/box_env.h"

#include "voca_render/voca_render.h"
#include "../controller.h"

void setup_render_layer()
{
    for (int i = 0; i < NUM_OF_LAYER; i++)
    {
        std::string tab_name;
        std::string key;
        int *index = new int(i);
        std::string iStr = toString(i);
        tab_name = "Layer ";
        tab_name += iStr;

        key = "enLyr_";
        key += iStr;
        vocaRender.renderSwitch(
            tab_name.c_str(), key.c_str(),
            R"({
                    "name":"Chạy",
                    "newLine":true
                })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                if (!value.compare("true"))
                    box_enable(li);
                else
                    box_disable(li);
            },
            (void *)index);

        vocaRender.renderSwitch(
            tab_name.c_str(), "rndTmrMd",
            R"({
                    "name":"Timer Mode",
                    "newLine":true
                })",
            [](std::string key, std::string value, void *param)
            {
                if (!value.compare("true"))
                {
                    onTimerMode();
                }
                else
                {
                    offTimerMode();
                }
            },
            NULL);

        vocaRender.renderSwitch(
            tab_name.c_str(), "msMd",
            R"({
                    "name":"Music Mode",
                    "newLine":true
                })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                if (!value.compare("true"))
                {
                    box_setMusicMode(li, true);
                }
                else
                {
                    box_setMusicMode(li, false);
                }
            },
            (void *)index);

        key = "save_layer_";
        key += std::string(iStr);
        vocaRender.renderButton(
            tab_name.c_str(), key.c_str(),
            R"({
                    "name":"Lưu",
                    "newLine":true
                })",
            [](std::string key, std::string value, void *param)
            {
                vocaStore.updateStore();
            },
            NULL);

        key = "brgLyr_";
        key += std::string(iStr);
        vocaRender.renderSlider(
            tab_name.c_str(), key.c_str(),
            R"({
                    "name":"Độ sáng",
                    "min":0,
                    "max":255,
                    "newLine":true
                })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                box_setBrightness(li, atoi(value.c_str()));
            },
            (void *)index);

        key = "clLyr_";
        key += std::string(iStr);
        vocaRender.renderSelect(
            tab_name.c_str(), key.c_str(),
            R"({
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
                })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                box_setColor(li, atoi(value.c_str()));
            },
            (void *)index);

        key = "cl0Lyr_";
        key += std::string(iStr);
        vocaRender.renderColorPicker(
            tab_name.c_str(), key.c_str(), R"({
            "name":"Màu 0"
          })",
            [](std::string key, std::string value, void *param) {
            },
            NULL);

        key = "cl1Lyr_";
        key += std::string(iStr);
        vocaRender.renderColorPicker(
            tab_name.c_str(), key.c_str(), R"({
            "name":"Màu 1"
          })",
            [](std::string key, std::string value, void *param) {
            },
            NULL);

        key = "cl2Lyr_";
        key += std::string(iStr);
        vocaRender.renderColorPicker(
            tab_name.c_str(), key.c_str(), R"({
            "name":"Màu 2",
            "newLine":true
          })",
            [](std::string key, std::string value, void *param) {
            },
            NULL);

        key = "mdLyr_";
        key += std::string(iStr);
        key += "_prv";
        vocaRender.renderButton(
            tab_name.c_str(), key.c_str(), R"({
    "name":"Prev"
  })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                box_prevMode(li);
            },
            (void *)index);

        key = "mdLyr_";
        key += std::string(iStr);
        key += "_rnd";
        vocaRender.renderButton(
            tab_name.c_str(), key.c_str(), R"({
    "name":"Random",
    "newLine":true
  })",
            [](std::string key, std::string value, void *param)
            {
                box_randomModeAll();
            },
            NULL);

        key = "mdLyr_";
        key += std::string(iStr);
        key += "_nxt";
        vocaRender.renderButton(
            tab_name.c_str(), key.c_str(), R"({
    "name":"Next",
    "newLine":true
  })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                box_nextMode(li);
            },
            (void *)index);

        key = "mdLyr_";
        key += std::string(iStr);
        vocaRender.renderSelect(
            tab_name.c_str(), key.c_str(), R"({
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
  })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                box_setMode(li, atoi(value.c_str()));
            },
            (void *)index);

        key = "spdLyr_";
        key += std::string(iStr);
        vocaRender.renderInput(
            tab_name.c_str(), key.c_str(), R"({
    "name":"Tốc độ",
    "newLine":true
  })",
            [](std::string key, std::string value, void *param)
            {
                int li = *((int *)param);
                box_setSpeed(li, atoi(value.c_str()));
            },
            (void *)index);
    };
};