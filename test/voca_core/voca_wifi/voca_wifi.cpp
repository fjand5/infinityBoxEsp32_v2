#include "voca_wifi.h"
VocaWifi vocaWifi;

#if 1
static void scanWifi()
{
  DynamicJsonDocument doc(2048);
  JsonArray array = doc.to<JsonArray>();
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  int scanResult;

  log_d("Starting WiFi scan...");

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0)
  {
    log_d("No networks found");
  }
  else if (scanResult > 0)
  {
    for (int8_t i = 0; i < scanResult; i++)
    {
      JsonObject nestedObj = array.createNestedObject();
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel);
      nestedObj["ssid"] = WiFi.SSID(i);
      nestedObj["rssi"] = WiFi.RSSI(i);
      delay(0);
    }
  }
  else
  {
  }
  String ret;
  serializeJson(array, ret);
  vocaWebserver.send(200, "application/json", ret.c_str());
}
static void setWifi()
{
  DynamicJsonDocument doc(256);
  auto err = deserializeJson(doc, vocaWebserver.arg(0));

  if (!err)
  {
    vocaStore.setValue("_ssid", doc["ssid"], true);
    vocaStore.setValue("_sspw", doc["sspw"], true);
  }
  vocaWebserver.send(200, "application/json", vocaWebserver.arg(0));
}
static void getWifi()
{
  DynamicJsonDocument doc(256);
  JsonObject obj = doc.to<JsonObject>();
  std::string value = vocaStore.getValue("_ssid");
  obj["wifi"] = value;
  obj["ip"] = WiFi.localIP().toString();
  std::string ret;
  serializeJson(obj, ret);
  vocaWebserver.send(200, "application/json", ret.c_str());
}

#endif
static void cbWiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (vocaStore.checkKey("_ssid") && vocaStore.checkKey("_sspw"))
  {

    std::string _ssid = vocaStore.getValue("_ssid");
    std::string _sspw = vocaStore.getValue("_sspw");
    WiFi.begin(_ssid.c_str(), _sspw.c_str());

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      log_d(".");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      vocaStatus.setStatus(Status_WifiStation_Connected);
    }
  }
}
// static void scanWifi(){};

VocaWifi::VocaWifi(/* args */)
{
}
void VocaWifi::begin()
{
  vocaStatus.waitStatus(Status_Store_Initialized);
  WiFi.mode(WIFI_AP_STA);

  if (vocaStore.checkKey("_apid") && vocaStore.checkKey("_appw"))
  {
    std::string _apid = vocaStore.getValue("_apid");
    std::string _appw = vocaStore.getValue("_appw");
    char *apid = new char[_apid.length() + 1]();
    char *appw = new char[_appw.length() + 1]();
    strcpy(apid, _apid.c_str());
    strcpy(appw, _appw.c_str());
    WiFi.softAP(apid, appw);
  }
  else
  {
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    String apid = String(APID) + "-" + mac;
    WiFi.softAP(apid.c_str(), APPW);
  }
  if (!vocaStore.checkKey("_ssid") || !vocaStore.checkKey("_sspw"))
  {
    vocaStore.setValue("_ssid", "Vong Cat-Hide");
    vocaStore.setValue("_sspw", "78787878");
  }

  std::string _ssid = vocaStore.getValue("_ssid");
  std::string _sspw = vocaStore.getValue("_sspw");

  char *ssid = new char[_ssid.length() + 1]();
  char *sspw = new char[_sspw.length() + 1]();
  strcpy(ssid, _ssid.c_str());
  strcpy(sspw, _sspw.c_str());
  log_e("%s : %s", ssid, sspw);
  WiFi.begin(ssid, sspw);
  while (WiFi.status() != WL_CONNECTED && millis() < WAIT_TO_CONNECT_STA)
  {
    delay(500);
    log_d(".");
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_AP);
    log_w("Only AP mode");
  }
  else
  {
    log_d("\nConnected to: %s", WiFi.SSID().c_str());
    WiFi.onEvent(cbWiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
    vocaStatus.setStatus(Status_WifiStation_Connected);
  }

  vocaWebserver.addHttpApi("scanWifi", scanWifi);
  vocaWebserver.addHttpApi("setWifi", setWifi);
  vocaWebserver.addHttpApi("getWifi", getWifi);
  vocaStatus.setStatus(Status_SetupWifi_Done);
}
