#pragma once
#include "box/box_controler.h"
#include "voca_render/voca_render.h"
void setup_render_config()
{
  // Mặt trước
  vocaRender.renderInput(F("Config"), F("sg_ft_1"), F(R"({
  })"),
              box_config_segment);

  vocaRender.renderSwitch(F("Config"), F("sg_ft_1_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  vocaRender.renderInput(F("Config"), F("sg_ft_2"), F(R"({
  })"),
              box_config_segment);

  vocaRender.renderSwitch(F("Config"), F("sg_ft_2_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  vocaRender.renderInput(F("Config"), F("sg_ft_3"), F(R"({
  })"),
              box_config_segment);

  vocaRender.renderSwitch(F("Config"), F("sg_ft_3_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  vocaRender.renderInput(F("Config"), F("sg_ft_4"), F(R"({
  })"),
              box_config_segment);

  vocaRender.renderSwitch(F("Config"), F("sg_ft_4_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  vocaRender.renderButton(F("Config"), F("shw_sg_ft"), F(R"({
    "name":"View Font Face",
    "newLine":true
  })"),box_config_show_face);

  // Mặt sau
  vocaRender.renderInput(F("Config"), F("sg_bk_1"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bk_1_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  vocaRender.renderInput(F("Config"), F("sg_bk_2"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bk_2_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_bk_3"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bk_3_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_bk_4"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bk_4_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderButton(F("Config"), F("shw_sg_bk"), F(R"({
    "name":"View Back Face",
    "newLine":true
  })"),box_config_show_face);
  // Mặt trên
  vocaRender.renderInput(F("Config"), F("sg_tp_1"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_tp_1_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_tp_2"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_tp_2_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_tp_3"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_tp_3_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_tp_4"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_tp_4_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderButton(F("Config"), F("shw_sg_tp"), F(R"({
    "name":"View Top Face",
    "newLine":true
  })"),box_config_show_face);
  // Măt dưới
  vocaRender.renderInput(F("Config"), F("sg_bt_1"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bt_1_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_bt_2"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bt_2_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_bt_3"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bt_3_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_bt_4"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_bt_4_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderButton(F("Config"), F("shw_sg_bt"), F(R"({
    "name":"View Bottom Face",
    "newLine":true
  })"),box_config_show_face);
  // Mặt trái
  vocaRender.renderInput(F("Config"), F("sg_lf_1"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_lf_1_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_lf_2"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_lf_2_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_lf_3"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_lf_3_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_lf_4"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_lf_4_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderButton(F("Config"), F("shw_sg_lf"), F(R"({
    "name":"View Left Face",
    "newLine":true
  })"),box_config_show_face);
  // Mặt phải
  vocaRender.renderInput(F("Config"), F("sg_rg_1"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_rg_1_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_rg_2"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_rg_2_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_rg_3"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_rg_3_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderInput(F("Config"), F("sg_rg_4"), F(R"({
  })"),
              box_config_segment);
  vocaRender.renderSwitch(F("Config"), F("sg_rg_4_rv"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  vocaRender.renderButton(F("Config"), F("shw_sg_rg"), F(R"({
    "name":"View Right Face",
    "newLine":true
  })"),box_config_show_face);
}