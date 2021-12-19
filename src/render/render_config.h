#include "box/box_controler.h"
#include "voca_render.h"
void setup_render_config()
{
    // Mặt trước
    renderInput(F("Config"), F("seg_font_1"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_font_1_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_font_2"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_font_2_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_font_3"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_font_3_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_font_4"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_font_4_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderButton(F("Config"), F("done_config_font_face"), F(R"({
    "name":"View Font Face",
    "newLine":true
  })"),
                 [](String key, String value) {
                 });

    // Mặt sau
    renderInput(F("Config"), F("seg_back_1"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_back_1_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_back_2"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_back_2_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_back_3"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_back_3_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_back_4"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_back_4_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderButton(F("Config"), F("done_config_back_face"), F(R"({
    "name":"View Back Face",
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    // Mặt trên
    renderInput(F("Config"), F("seg_top_1"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_top_1_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_top_2"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_top_2_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_top_3"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_top_3_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_top_4"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_top_4_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderButton(F("Config"), F("done_config_top_face"), F(R"({
    "name":"View Top Face",
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    // Măt dưới
    renderInput(F("Config"), F("seg_bottom_1"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_bottom_1_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_bottom_2"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_bottom_2_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_bottom_3"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_bottom_3_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_bottom_4"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_bottom_4_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderButton(F("Config"), F("done_config_bottom_face"), F(R"({
    "name":"View Bottom Face",
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    // Mặt trái
    renderInput(F("Config"), F("seg_left_1"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_left_1_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_left_2"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_left_2_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_left_3"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_left_3_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_left_4"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_left_4_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderButton(F("Config"), F("done_config_left_face"), F(R"({
    "name":"View Left Face",
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    // Mặt phải
    renderInput(F("Config"), F("seg_right_1"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_right_1_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_right_2"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_right_2_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_right_3"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_right_3_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderInput(F("Config"), F("seg_right_4"), F(R"({
    "name":"Mật khẩu wifi"
  })"),
                [](String key, String value) {
                });
    renderSwitch(F("Config"), F("seg_right_4_rev"), F(R"({
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
    renderButton(F("Config"), F("done_config_right_face"), F(R"({
    "name":"View Right Face",
    "newLine":true
  })"),
                 [](String key, String value) {
                 });
}