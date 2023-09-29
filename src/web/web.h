#include <DNSServer.h>
#include "esp_ota_ops.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "HTTPUpdateAsyncServer.h"
#include <StreamString.h>
#include <ArduinoJson.h>

#define PREF_WEB_NAME "__web"

// getterFunc là hàm trả về giá trị trước và sau khi set
// setterBlock là khối lệnh cho việc set
// docSize là lượng bộ nhớ cấp cho document json

#define ADD_SETTER_AFFTER_ROUTE(uri, getterFunc, setterBlock, affterBlock, docSize) \
    addRoute(                                                                       \
        uri,                                                                        \
        [=](AsyncWebServerRequest *request)                                         \
        {                                                                           \
            DynamicJsonDocument _doc(docSize);                                      \
            JsonObject obj = _doc.to<JsonObject>();                                 \
            String value = request->arg("value");                                   \
            obj["oldValue"] = getterFunc;                                           \
            {setterBlock};                                                          \
            obj["newValue"] = getterFunc;                                           \
            String ret;                                                             \
            serializeJson(obj, ret);                                                \
            AsyncWebServerResponse *response =                                      \
                request->beginResponse(200, String("application/json"), ret);       \
            request->send(response);                                                \
            {                                                                       \
                affterBlock                                                         \
            }                                                                       \
        });
#define ADD_SETTER_ROUTE(uri, getterFunc, setterBlock, docSize)               \
    addRoute(                                                                 \
        uri,                                                                  \
        [=](AsyncWebServerRequest *request)                               \
        {                                                                     \
            DynamicJsonDocument _doc(docSize);                                \
            JsonObject obj = _doc.to<JsonObject>();                           \
            String value = request->arg("value");                             \
            obj["oldValue"] = getterFunc;                                     \
            {setterBlock};                                                    \
            obj["newValue"] = getterFunc;                                     \
            String ret;                                                       \
            serializeJson(obj, ret);                                          \
            AsyncWebServerResponse *response =                                \
                request->beginResponse(200, String("application/json"), ret); \
            request->send(response);                                          \
        });
#define ADD_GETTER_ROUTE(uri, getterBlock, docSize)                           \
    addRoute(                                                                 \
        uri,                                                                  \
        [=](AsyncWebServerRequest *request)                                   \
        {                                                                     \
            DynamicJsonDocument _doc(docSize);                                \
            JsonObject obj = _doc.to<JsonObject>();                           \
            {getterBlock} String ret;                                         \
            serializeJson(obj, ret);                                          \
            AsyncWebServerResponse *response =                                \
                request->beginResponse(200, String("application/json"), ret); \
            request->send(response);                                          \
        });

// typedef std::function<void(AsyncWebServerRequest *)> RouteFunction;

void addRoute(String uri, ArRequestHandlerFunction handler);
void webBegin(bool forceDefault);
