#pragma once

#include "voca_env.h"
#include "voca_webserver/voca_webserver.h"

void renderUI()
{
  vocaRender.renderInput(
      "System", "_apid", R"({
    "name":"Tên wifi",
    "description":"",
    "newLine":true,
    "span":{
      
    }
  })",
      [](std::string key, std::string value, void *param)
      {
        vocaStore.setValue(key, value, true);
      },
      NULL);
  vocaRender.renderInput(
      "System", "_appw", R"({
    "name":"Mật khẩu wifi",
    "description":"",
    "newLine":true,
    "password":true
  })",
      [](std::string key, std::string value, void *param)
      {
        vocaStore.setValue(key, value, true);
      },
      NULL);
  vocaRender.renderButton(
      "System", "_reset", R"({
    "name":"Khởi động lại",
    "description":"",
    "confirm":"Bạn có chắc muốn khởi động lại hệ thống không?",
    "span":{}
  })",
      [](std::string key, std::string value, void *param)
      {
        ESP.restart();
      },
      NULL);
  vocaRender.renderButton(
      "System", "_format", R"({
    "name":"Xóa dữ liệu",
    "description":"",
    "newLine":true,
    "confirm":"Bạn có chắc muốn xóa toàn bộ dữ liệu không?",
    "span":{
    }
  })",
      [](std::string key, std::string value, void *param)
      {
        SPIFFS.format();
      },
      NULL);
  vocaRender.renderInput(
      "System", "_version", R"({
    "name":"Phiên bản",
    "description":""
  })",
      [](std::string key, std::string value, void *param) {
      },
      NULL);
}
void setupSystem()
{
  renderUI();
  vocaWebserver
      .addHttpApi(
          "/manifest",
          []()
          {
            std::string manifestData;
            DynamicJsonDocument docManifest(1024);
            JsonObject manifestObject = docManifest.to<JsonObject>();
#ifdef AUTH_FEATURE
            manifestObject["auth"] = true;
#endif
            manifestObject["mqtt"] = false;
            manifestObject["wifiSta"] = true;
            manifestObject["creator"] = "huynhtheluat@gmail.com";

            serializeJson(manifestObject, manifestData);
            String content = String(manifestData.c_str());
            vocaWebserver.send(200, F("application/json"), content);
          },
          false);
  vocaWebserver
      .addHttpApi("/reset", []()
                  {
        log_w("Reset system");
        vocaWebserver.send(200);
        delay(500); // chờ send thành công.
        ESP.restart(); });
}