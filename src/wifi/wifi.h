

#define AP_SSID_DEFAULT "MaTrix"
#define AP_PASS_DEFAULT "12345678"

#define PREF_WIFI_NAME "__wifi"
#define AP_SSID_PREF_KEY "_apid"
#define AP_PASS_PREF_KEY "_appw"

#define STA_SSID_PREF_KEY "_staid"
#define STA_PASS_PREF_KEY "_stapw"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <WiFi.h>
#include "../web/web.h"
void wifiBegin(bool forceDefault);
void clearWifiData();
