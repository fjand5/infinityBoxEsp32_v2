#pragma once
#include "voca_env.h"
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include <list>

WebSocketsServer webSocket = WebSocketsServer(81);
SemaphoreHandle_t websocket_sem;
typedef void (*OnWSTextIncome)(JsonObject);
std::list<OnWSTextIncome> OnWSTextIncomes;
void setOnWSTextIncome(OnWSTextIncome cb)
{
    OnWSTextIncomes.push_front(cb);
}
void onConnect(uint8_t num, uint8_t *payload, size_t length)
{
    String token = "";
    for (int i = 0; i < length; i++)
    {
        token += (char)payload[i];
    }
    token.replace("/", "");

    if (!check_auth_jwt(token))
    {
        log_d("token: %s num: %d", token.c_str(), num);
        xSemaphoreGive(websocket_sem);
        webSocket.disconnect(num);
    }
    else
    {
        log_d("token: %s num: %d", token.c_str(), num);
    }
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    if (xSemaphoreTake(websocket_sem, portMAX_DELAY) == pdTRUE)
    {
        switch (type)
        {
        case WStype_DISCONNECTED:
        {
            break;
        }
        case WStype_CONNECTED:
        {
            onConnect(num, payload, length);
            break;
        }
        case WStype_TEXT:
        {

            DynamicJsonDocument _doc(2048);
            deserializeJson(_doc, payload, length);
            JsonObject obj = _doc.as<JsonObject>();
            String ret;
            if (obj["cmd"] == "exe")
            {
                for (auto const &item : OnWSTextIncomes)
                {
                    if (item != NULL)
                        item(obj);
                }
                String _key = obj["espKey"];
                obj = _doc.to<JsonObject>();
                getValueByObject(_key, obj);

                String tmp;
                serializeJsonPretty(_doc, tmp);
                log_d("serializeJsonPretty: %s", tmp.c_str());
            }
            else if (obj["cmd"] == "gal")
            {
                obj = _doc.to<JsonObject>();
                getValuesByObject(obj);
            }
            else if (obj["cmd"] == "ping")
            {
                obj = _doc.to<JsonObject>();
                obj["cmd"] = "pong";
                obj["stamp"] = millis();
            }
            // dùng luôn _doc để lấy giá trị
            serializeJson(_doc, ret);
            webSocket.broadcastTXT(ret);
            break;
        }
        case WStype_BIN:
            break;
        case WStype_ERROR:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
        }
        xSemaphoreGive(websocket_sem);
    }
}

void setupWebSocket()
{
    
    WAIT_FLAG_SET(FLAG_SETUP_WIFI_DONE);
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            WebSocketsServer* _webSocket = (WebSocketsServer*)param;
            log_w("loopSocket is running on core: %d", xPortGetCoreID());
            _webSocket->begin();
            _webSocket->onEvent(webSocketEvent);
            websocket_sem = xSemaphoreCreateBinary();
            xSemaphoreGive(websocket_sem);
            SET_FLAG(FLAG_WEBSOCKET_READY);
            WAIT_FLAG_SET(FLAG_WEBSERVER_READY | FLAG_WEBSOCKET_READY);
            log_w("loopSocket is running on core: %d", xPortGetCoreID());

            while (1)
            {
                _webSocket->loop();
                delay(10);
            }
        },
        "loopSocket",
        20000,
        (void *) &webSocket,
        2,
        NULL,
        VOCA_CORE_CPU);
}

void loopWebSocket()
{
}