#pragma once
#include "box/box_controller.h"
#include "voca_render/voca_render.h"
#include "voca_store/voca_store.h"
void setup_color_setting()
{
  // Mặt trước
  vocaRender.renderSelect(
      "Color", String("clSel"),
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
        vocaStore.setValue(key, value);
      },
      NULL);

  vocaRender.renderColorPicker(
      "Color", String("clSel0"), F(R"({
            "name":"Màu 0"
          })"),
      [](String key, String value, void *param) {
      },
      NULL);
  vocaRender.renderColorPicker(
      "Color", String("clSel1"), F(R"({
            "name":"Màu 1"
          })"),
      [](String key, String value, void *param) {
      },
      NULL);
  vocaRender.renderColorPicker(
      "Color", String("clSel2"), F(R"({
            "name":"Màu 2",
            "newLine":true
          })"),
      [](String key, String value, void *param) {
      },
      NULL);
}