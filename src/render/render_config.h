#include "box/box_controler.h"
#include "voca_render.h"
void setup_render_config()
{
  // Mặt trước
  renderInput(F("Config"), F("seg_font_1"), F(R"({
  })"),
              box_config_segment);

  renderSwitch(F("Config"), F("seg_font_1_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  renderInput(F("Config"), F("seg_font_2"), F(R"({
  })"),
              box_config_segment);

  renderSwitch(F("Config"), F("seg_font_2_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  renderInput(F("Config"), F("seg_font_3"), F(R"({
  })"),
              box_config_segment);

  renderSwitch(F("Config"), F("seg_font_3_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  renderInput(F("Config"), F("seg_font_4"), F(R"({
  })"),
              box_config_segment);

  renderSwitch(F("Config"), F("seg_font_4_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  renderButton(F("Config"), F("show_seg_font"), F(R"({
    "name":"View Font Face",
    "newLine":true
  })"),box_config_show_face);

  // Mặt sau
  renderInput(F("Config"), F("seg_back_1"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_back_1_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);

  renderInput(F("Config"), F("seg_back_2"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_back_2_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_back_3"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_back_3_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_back_4"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_back_4_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderButton(F("Config"), F("show_seg_back"), F(R"({
    "name":"View Back Face",
    "newLine":true
  })"),box_config_show_face);
  // Mặt trên
  renderInput(F("Config"), F("seg_top_1"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_top_1_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_top_2"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_top_2_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_top_3"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_top_3_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_top_4"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_top_4_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderButton(F("Config"), F("show_seg_top"), F(R"({
    "name":"View Top Face",
    "newLine":true
  })"),box_config_show_face);
  // Măt dưới
  renderInput(F("Config"), F("seg_bottom_1"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_bottom_1_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_bottom_2"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_bottom_2_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_bottom_3"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_bottom_3_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_bottom_4"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_bottom_4_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderButton(F("Config"), F("show_seg_bottom"), F(R"({
    "name":"View Bottom Face",
    "newLine":true
  })"),box_config_show_face);
  // Mặt trái
  renderInput(F("Config"), F("seg_left_1"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_left_1_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_left_2"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_left_2_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_left_3"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_left_3_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_left_4"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_left_4_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderButton(F("Config"), F("show_seg_left"), F(R"({
    "name":"View Left Face",
    "newLine":true
  })"),box_config_show_face);
  // Mặt phải
  renderInput(F("Config"), F("seg_right_1"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_right_1_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_right_2"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_right_2_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_right_3"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_right_3_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderInput(F("Config"), F("seg_right_4"), F(R"({
  })"),
              box_config_segment);
  renderSwitch(F("Config"), F("seg_right_4_rev"), F(R"({
    "newLine":true
  })"),
               box_config_segment);
  renderButton(F("Config"), F("show_seg_right"), F(R"({
    "name":"View Right Face",
    "newLine":true
  })"),box_config_show_face);
}