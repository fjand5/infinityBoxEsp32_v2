#pragma once

#include "voca_env.h"
#include "voca_render.h"
#include "voca_status/voca_status.h"
#include "voca_wifi/voca_wifi.h"
#include "voca_webserver/voca_webserver.h"
#include "voca_store/voca_store.h"
#include "voca_system.h"
#include "voca_websocket/voca_websocket.h"
void renderUI()
{
    renderInput(F("System"), F("_apid"), F(R"({
    "name":"Tên wifi",
    "description":"",
    "newLine":true,
    "span":{
      
    }
  })"),
                [](String key, String value)
                {
                    vocaStore.setValue(key, value, true);
                });
    renderInput(F("System"), F("_appw"), F(R"({
    "name":"Mật khẩu wifi",
    "description":"",
    "newLine":true,
    "password":true
  })"),
                [](String key, String value)
                {
                    vocaStore.setValue(key, value, true);
                });
    renderButton(F("System"), F("_reset"), F(R"({
    "name":"Khởi động lại",
    "description":"",
    "confirm":"Bạn có chắc muốn khởi động lại hệ thống không?",
    "span":{}
  })"),
                 [](String key, String value)
                 {
                     ESP.restart();
                 });
    renderButton(F("System"), F("_format"), F(R"({
    "name":"Xóa dữ liệu",
    "description":"",
    "newLine":true,
    "confirm":"Bạn có chắc muốn xóa toàn bộ dữ liệu không?",
    "span":{
    }
  })"),
                 [](String key, String value)
                 {
                     SPIFFS.format();
                 });
    renderInput(F("System"), F("_version"), F(R"({
    "name":"Phiên bản",
    "description":""
  })"),
                [](String key, String value) {
                });
}
void setup_voca()
{
    vocaStore.begin();
    setupRender();
    vocaWifi.begin();
    vocaWebserver.begin();
    vocaWebsocket.begin();
    setupSystem();

    renderUI();

    vocaStatus.waitAllStatus();

}