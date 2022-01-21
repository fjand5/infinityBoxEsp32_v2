#pragma once
#include "voca_env.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include "voca_store.h"
#include "voca_webserver.h"
#include "voca_status.h"
#include "voca_render.h"

#define APID "vocaui"
#define APPW "12345678"
void scanWifi();
void setWifi();
void getWifi();
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  SET_FLAG(FLAG_CONNECTED_STA);
  if (checkKey("_ssid") && checkKey("_sspw"))
  {
    WiFi.begin(getValueByCStr("_ssid"), getValueByCStr("_sspw"));
    // WiFi.begin("Vong Cat 3", "78787878");

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      log_d(".");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      SET_FLAG(FLAG_CONNECTED_STA);
    }
  }
}
void setupWifi(void)
{
  WAIT_FLAG_SET(FLAG_INITIALIZED_STORE);
  renderInput(F("System"), F("_apid"), F(R"({
    "name":"Tên wifi",
    "description":"",
    "newLine":true,
    "span":{
      
    }
  })"),
               [](String key, String value)
               {
                 setValue(key,value);
               });
  renderInput(F("System"), F("_appw"), F(R"({
    "name":"Mật khẩu wifi",
    "description":"",
    "newLine":true,
    "password":true
  })"),
               [](String key, String value)
               {
                 setValue(key,value);
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
                 LITTLEFS.format();
               });
  renderInput(F("System"), F("_version"), F(R"({
    "name":"Phiên bản",
    "description":""
  })"),
               [](String key, String value)
               {
               });
  //   renderColorPicker("Color", "_color", R"({
  //   "name":"Xóa dữ liệu",
  //   "description":"",
  //   "span":6
  // })",
  //              [](String key, String value)
  //              {
  //                setValue(key,value);

  //                log_d("key: %s; value: %s",key.c_str(), value.c_str());
  //              });
  //   renderSelect("Color", "_select", R"({
  //   "name":"Lựa chọn",
  //   "description":"",
  //   "options":["một","hai","ba","bốn"],
  //   "span":6
  // })",
  //              [](String key, String value)
  //              {
  //                setValue(key,value);

  //                log_d("key: %s; value: %s",key.c_str(), value.c_str());
  //              });
  WiFi.mode(WIFI_AP_STA);
  if (checkKey("_apid") && checkKey("_appw"))
  {
    WiFi.softAP(getValueByCStr("_apid"), getValueByCStr("_appw"));
  }
  else
  {
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    String apid = String(APID) + "-" + mac;
    WiFi.softAP(apid.c_str(), APPW);
  }

  // if (checkKey("_ssid") && checkKey("_sspw"))
  // {
    WiFi.begin(getValueByCStr("_ssid","Vong Cat-Hide"), getValueByCStr("_sspw","78787878"));
    // WiFi.begin("Vong Cat-Hide", "78787878");

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      log_d(".");
    }
  // }
  // WiFi.begin("Vong Cat-Hide", "78787878");

  // Wait for connection
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_AP);
    log_d("Only AP mode");
  }
  else
  {
    log_d("");
    log_d("Connected to ");
    log_d("%s",getValue("_ssid").c_str());
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
    SET_FLAG(FLAG_CONNECTED_STA);
  }

  addHttpApi("scanWifi", scanWifi);
  addHttpApi("setWifi", setWifi);
  addHttpApi("getWifi", getWifi);
  SET_FLAG(FLAG_SETUP_WIFI_DONE);

}

void loopWifi(void)
{
}

void scanWifi()
{
  DynamicJsonDocument doc(2048);
  JsonArray array = doc.to<JsonArray>();
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  log_d("Starting WiFi scan...");

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0)
  {
    log_d("No networks found");
  }
  else if (scanResult > 0)
  {
    // Serial.printf(PSTR("%d networks found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++)
    {
      JsonObject nestedObj = array.createNestedObject();
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel);
      nestedObj["ssid"] = WiFi.SSID(i);
      nestedObj["rssi"] = WiFi.RSSI(i);

      // Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
      //               i,
      //               channel,
      //               bssid[0], bssid[1], bssid[2],
      //               bssid[3], bssid[4], bssid[5],
      //               rssi,
      //               WiFi.encryptionType(i) ? ' ' : '*',
      //               hidden ? 'H' : 'V',
      //               ssid.c_str());
      delay(0);
    }
  }
  else
  {
    // Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
  String ret;
  serializeJson(array, ret);
  server.send(200, "application/json", ret.c_str());
}

void setWifi()
{
  DynamicJsonDocument doc(256);
  auto err = deserializeJson(doc, server.arg(0));

  if (!err)
  {
    setValue("_ssid", doc["ssid"], true);
    setValue("_sspw", doc["sspw"], true);
  }
  server.send(200, "application/json", server.arg(0));
}
void getWifi()
{
  DynamicJsonDocument doc(256);
  JsonObject obj = doc.to<JsonObject>();
  obj["wifi"] = getValue("_ssid");
  obj["ip"] = WiFi.localIP().toString();
  String ret;
  serializeJson(obj, ret);
  server.send(200, "application/json", ret);
}