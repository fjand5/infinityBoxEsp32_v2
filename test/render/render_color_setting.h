#pragma once
#include "box/box_controller.h"
#include "voca_render/voca_render.h"
void setup_color_setting()
{
    vocaRender.renderSwitch(
        "Color", "rndClTm", R"({
    "name":"Tự chuyển màu",
    "newLine":true
  })",
        [](std::string key, std::string value, void *param)
        {
        
            if ( !value.compare("true"))
            {
                box_setTimerRandomColor(true);
            }
            else
            {
                box_setTimerRandomColor(false);
            }

        },
        NULL);
    vocaRender.renderSelect(
        "Color", "clSel",
        R"({
                    "name":"Mẫu màu",
                    "options":[
                    "00","01","02","03","04","05","06","07","08","09","10","11","12","13","14"],
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
            box_setCurrentSelectColor(atoi(value.c_str()));
        },
        NULL);

    vocaRender.renderColorPicker(
        "Color", "clSel0", R"({
            "name":"Màu 0"
          })",
        [](std::string key, std::string value, void *param)
        {
            box_modifyColor(0, value);
        },
        NULL);
    vocaRender.renderColorPicker(
        "Color", "clSel1", R"({
            "name":"Màu 1"
          })",
        [](std::string key, std::string value, void *param)
        {
            box_modifyColor(1, value);
        },
        NULL);
    vocaRender.renderColorPicker(
        "Color", "clSel2", R"({
            "name":"Màu 2",
            "newLine":true
          })",
        [](std::string key, std::string value, void *param)
        {
            box_modifyColor(2, value);
        },
        NULL);

    vocaRender.renderButton(
        "Color", "dfCl", R"({
    "name":"Default"
  })",
        [](std::string key, std::string value, void *param)
        {
            box_defaultColor();
        },
        NULL);
}