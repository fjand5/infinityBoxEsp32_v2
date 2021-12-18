#include "box/box_controler.h"
#include "voca_render.h"
void setup_render_config()
{
    // Mặt trước
    renderInput("Config", "seg_font_1", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_font_1_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_font_2", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_font_2_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_font_3", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_font_3_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_font_4", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_font_4_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderButton("Config", "done_config_font_face", R"({
    "name":"View Font Face",
    "newLine":true
  })",
                 [](String key, String value) {
                 });

    // Mặt sau
    renderInput("Config", "seg_back_1", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_back_1_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_back_2", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_back_2_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_back_3", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_back_3_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_back_4", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_back_4_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderButton("Config", "done_config_back_face", R"({
    "name":"View Back Face",
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    // Mặt trên
    renderInput("Config", "seg_top_1", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_top_1_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_top_2", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_top_2_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_top_3", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_top_3_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_top_4", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_top_4_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderButton("Config", "done_config_top_face", R"({
    "name":"View Top Face",
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    // Măt dưới
    renderInput("Config", "seg_bottom_1", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_bottom_1_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_bottom_2", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_bottom_2_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_bottom_3", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_bottom_3_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_bottom_4", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_bottom_4_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderButton("Config", "done_config_bottom_face", R"({
    "name":"View Bottom Face",
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    // Mặt trái
    renderInput("Config", "seg_left_1", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_left_1_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_left_2", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_left_2_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_left_3", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_left_3_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_left_4", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_left_4_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderButton("Config", "done_config_left_face", R"({
    "name":"View Left Face",
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    // Mặt phải
    renderInput("Config", "seg_right_1", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_right_1_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_right_2", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_right_2_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_right_3", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_right_3_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderInput("Config", "seg_right_4", R"({
  })",
                [](String key, String value) {
                });
    renderSwitch("Config", "seg_right_4_rev", R"({
    "newLine":true
  })",
                 [](String key, String value) {
                 });
    renderButton("Config", "done_config_right_face", R"({
    "name":"View Right Face",
    "newLine":true
  })",
                 [](String key, String value) {
                 });
}