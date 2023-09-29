#pragma once
#include "box/box_controller.h"
#include "voca_render/voca_render.h"
void setup_render_config()
{
  // Mặt trước
  vocaRender.renderInput("Config", "sg_ft_1", R"({
  })",
              box_config_segment, NULL);

  vocaRender.renderSwitch("Config", "sg_ft_1_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);

  vocaRender.renderInput("Config", "sg_ft_2", R"({
  })",
              box_config_segment, NULL);

  vocaRender.renderSwitch("Config", "sg_ft_2_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);

  vocaRender.renderInput("Config", "sg_ft_3", R"({
  })",
              box_config_segment, NULL);

  vocaRender.renderSwitch("Config", "sg_ft_3_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);

  vocaRender.renderInput("Config", "sg_ft_4", R"({
  })",
              box_config_segment, NULL);

  vocaRender.renderSwitch("Config", "sg_ft_4_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);

  vocaRender.renderButton("Config", "shw_sg_ft", R"({
    "name":"View Font Face",
    "newLine":true
  })",box_config_show_face, NULL);

  // Mặt sau
  vocaRender.renderInput("Config", "sg_bk_1", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bk_1_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);

  vocaRender.renderInput("Config", "sg_bk_2", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bk_2_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_bk_3", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bk_3_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_bk_4", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bk_4_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderButton("Config", "shw_sg_bk", R"({
    "name":"View Back Face",
    "newLine":true
  })",box_config_show_face, NULL);
  // Mặt trên
  vocaRender.renderInput("Config", "sg_tp_1", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_tp_1_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_tp_2", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_tp_2_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_tp_3", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_tp_3_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_tp_4", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_tp_4_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderButton("Config", "shw_sg_tp", R"({
    "name":"View Top Face",
    "newLine":true
  })",box_config_show_face, NULL);
  // Măt dưới
  vocaRender.renderInput("Config", "sg_bt_1", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bt_1_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_bt_2", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bt_2_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_bt_3", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bt_3_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_bt_4", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_bt_4_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderButton("Config", "shw_sg_bt", R"({
    "name":"View Bottom Face",
    "newLine":true
  })",box_config_show_face, NULL);
  // Mặt trái
  vocaRender.renderInput("Config", "sg_lf_1", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_lf_1_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_lf_2", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_lf_2_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_lf_3", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_lf_3_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_lf_4", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_lf_4_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderButton("Config", "shw_sg_lf", R"({
    "name":"View Left Face",
    "newLine":true
  })",box_config_show_face, NULL);
  // Mặt phải
  vocaRender.renderInput("Config", "sg_rg_1", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_rg_1_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_rg_2", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_rg_2_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_rg_3", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_rg_3_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderInput("Config", "sg_rg_4", R"({
  })",
              box_config_segment, NULL);
  vocaRender.renderSwitch("Config", "sg_rg_4_rv", R"({
    "newLine":true
  })",
               box_config_segment, NULL);
  vocaRender.renderButton("Config", "shw_sg_rg", R"({
    "name":"View Right Face",
    "newLine":true
  })",box_config_show_face, NULL);
}