#include "wifi.h"
Preferences pref;
String wifiList;
void clearWifiData()
{
  pref.clear();
};
void wifiBegin(bool forceDefault)
{
  pref.begin(PREF_WIFI_NAME);
  WiFi.mode(WIFI_AP_STA);

  String mac = WiFi.macAddress();
  mac.replace(":", "");
  String apid = String(AP_SSID_DEFAULT) + "-" + mac;
  // Dùng tên mặc định kết hợp với mac
  if (forceDefault)
  {
    WiFi.softAP(apid.c_str(),
                AP_PASS_PREF_KEY);
  }
  else
  {
    WiFi.softAP(pref.getString(AP_SSID_PREF_KEY, apid.c_str()).c_str(),
                pref.getString(AP_PASS_PREF_KEY, AP_PASS_DEFAULT).c_str());
  }

  addRoute("/setApSSID",
           [=](AsyncWebServerRequest *request)
           {
             DynamicJsonDocument _doc(1000);
             JsonObject obj = _doc.to<JsonObject>();
             String value = request->arg("value");

             obj["oldValue"] = pref.getString(AP_SSID_PREF_KEY, apid.c_str());
             /* update new value */
             pref.putString(AP_SSID_PREF_KEY, value);
             obj["newValue"] = pref.getString(AP_SSID_PREF_KEY, apid.c_str());
             /* */
             String ret;
             serializeJson(obj, ret);
             AsyncWebServerResponse *response =
                 request->beginResponse(200, String("application/json"), ret);
             request->send(response);
           });
  addRoute("/setApPASS",
           [=](AsyncWebServerRequest *request)
           {
             DynamicJsonDocument _doc(1000);
             JsonObject obj = _doc.to<JsonObject>();
             String value = request->arg("value");

             obj["oldValue"] = pref.getString(AP_PASS_PREF_KEY, AP_PASS_DEFAULT);
             /* update new value */
             pref.putString(AP_PASS_PREF_KEY, value);
             obj["newValue"] = pref.getString(AP_PASS_PREF_KEY, AP_PASS_DEFAULT);
             /* */
             String ret;
             serializeJson(obj, ret);
             AsyncWebServerResponse *response =
                 request->beginResponse(200, String("application/json"), ret);
             request->send(response);
           });
  addRoute("/setStaSSID",
           [=](AsyncWebServerRequest *request)
           {
             DynamicJsonDocument _doc(1000);
             JsonObject obj = _doc.to<JsonObject>();
             String value = request->arg("value");

             obj["oldValue"] = pref.getString(STA_SSID_PREF_KEY, "Vong Cat 3");
             /* update new value */
             pref.putString(STA_SSID_PREF_KEY, value);
             obj["newValue"] = pref.getString(STA_SSID_PREF_KEY, "Vong Cat 3");
             /* */
             String ret;
             serializeJson(obj, ret);
             AsyncWebServerResponse *response =
                 request->beginResponse(200, String("application/json"), ret);
             request->send(response);
           });
  addRoute("/setStaPASS",
           [=](AsyncWebServerRequest *request)
           {
             DynamicJsonDocument _doc(1000);
             JsonObject obj = _doc.to<JsonObject>();
             String value = request->arg("value");

             obj["oldValue"] = pref.getString(STA_PASS_PREF_KEY, "");
             /* update new value */
             pref.putString(STA_PASS_PREF_KEY, value);
             obj["newValue"] = pref.getString(STA_PASS_PREF_KEY, "");
             /* */
             String ret;
             serializeJson(obj, ret);
             AsyncWebServerResponse *response =
                 request->beginResponse(200, String("application/json"), ret);
             request->send(response);
           });

  addRoute("/getWifi",
           [=](AsyncWebServerRequest *request)
           {
             DynamicJsonDocument _doc(1000);
             JsonObject obj = _doc.to<JsonObject>();

             String mac = WiFi.macAddress();
             mac.replace(":", "");
             String apid = String(AP_SSID_DEFAULT) + "-" + mac;
             // Dùng tên mặc định kết hợp với mac

             obj["ApSSID"] = pref.getString(AP_SSID_PREF_KEY, apid.c_str());
             obj["ApPASS"] = pref.getString(AP_PASS_PREF_KEY, AP_PASS_DEFAULT);

             obj["StaSSID"] = pref.getString(STA_SSID_PREF_KEY, "");
             obj["StaPASS"] = pref.getString(STA_PASS_PREF_KEY, "");
             obj["ip"] = WiFi.localIP();
             String ret;
             serializeJson(obj, ret);
             AsyncWebServerResponse *response =
                 request->beginResponse(200, String("application/json"), ret);
             request->send(response);
           });
  addRoute("/nearWifi",
           [=](AsyncWebServerRequest *request)
           {
             int16_t scanResult = WiFi.scanNetworks();
             if (scanResult == WIFI_SCAN_FAILED)
             {
               request->send(200, String("text/html"), "WIFI_SCAN_FAILED");
               return;
             }
             if (scanResult == WIFI_SCAN_RUNNING)
             {
               request->send(200, String("text/html"), "WIFI_SCAN_RUNNING");
               return;
             }
             DynamicJsonDocument doc(3000);
             JsonArray array = doc.to<JsonArray>();
             String ssid;
             int32_t rssi;
             uint8_t encryptionType;
             uint8_t *bssid;
             int32_t channel;
             for (int8_t i = 0; i < scanResult; i++)
             {
               JsonObject nestedObj = array.createNestedObject();
               WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel);
               nestedObj["ssid"] = WiFi.SSID(i);
               nestedObj["rssi"] = WiFi.RSSI(i);
             }
             String ret;
             serializeJson(array, ret);
             request->send(200, String("text/html"), ret);
           });
  // WiFi.begin("Vong Cat 3", "78787878");
  // return;
  if (forceDefault)
    WiFi.begin("Vong Cat 3", "78787878");
  else
    xTaskCreatePinnedToCore(
        [=](void *p)
        {
          uint8_t countNotContected = 0;
          WiFi.begin(pref.getString(STA_SSID_PREF_KEY, "").c_str(), pref.getString(STA_PASS_PREF_KEY, "").c_str());
          while (1)
          {
            delay(3000);

            if (!pref.isKey(STA_SSID_PREF_KEY) || !pref.isKey(STA_PASS_PREF_KEY))
            {
              continue;
            }
            if (WiFi.status() != WL_CONNECTED)
            {
              countNotContected++;
            }
            else
            {
              countNotContected = 0;
              vTaskDelete(NULL);
            }
            if (countNotContected > 3)
            {
              WiFi.disconnect(true);
              WiFi.mode(WIFI_AP);
              countNotContected = 0;
              vTaskDelete(NULL);
            }
          }

          vTaskDelete(NULL);
        },
        PREF_WIFI_NAME,
        4000,
        NULL,
        0,
        NULL,
        1);
}