#pragma once
#include "../controller.h"
#include "voca_render/voca_render.h"
void setup_microphone()
{
    vocaRender.renderSlider(
        "Microphone", "micGain",
        R"({
                    "name":"Độ nhạy",
                    "min":0,
                    "max":100,
                    "newLine":true
                })",
        [](std::string key, std::string value, void *param)
        {
            setMicGain(value);
        },
        NULL);
    vocaRender.renderSlider(
        "Microphone", "micBeat",
        R"({
                    "name":"Lấy nhịp",
                    "min":0,
                    "max":100,
                    "newLine":true
                })",
        [](std::string key, std::string value, void *param)
        {
            setMicTakeBeat(value);
        },
        NULL);

    vocaRender.renderSelect(
        "Microphone", "msEff",
        R"({
                    "name":"Hiệu ứng",
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
            setMusicEffect(value);
        },NULL);
}