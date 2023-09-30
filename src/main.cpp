// #define MAC_ADDRESS "78e36d091a64"
// #define UPLOADER
#include "env.h"
#include <Arduino.h>
#if defined UPLOADER
#include "uploader.h"
#else
// #include "esp_ota_ops.h"
#include <nvs_flash.h>
#include "wifi/wifi.h"
#include "web/web.h"
#include "ui/ui.h"
#include "box/box.h"
#include "button/button.h"
// extern Box box;
// extern Button button;
boolean waitForUpdate = false;
void setup()
{
    // if (
    //     esp_reset_reason() != ESP_RST_POWERON ||
    //     esp_reset_reason() != ESP_RST_SW ||
    //     esp_reset_reason() != ESP_RST_BROWNOUT

    // )
    // {
    //     // Nếu quá trình khởi động bị lỗi thì chuyển sang phân vùng nhỏ để chạy upload
    //     esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_APP_OTA_0, "ota_0");
    //     const esp_partition_t *p = esp_partition_get(pi);
    //     esp_ota_set_boot_partition(p);
    // }
    pinMode(BUTTON_PIN, OUTPUT);
    digitalWrite(BUTTON_PIN, HIGH);
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        waitForUpdate = true;
    }
    if (waitForUpdate)
    {
        wifiBegin(true);
        webBegin(true);
    }
    else
    {
        wifiBegin(false);
        webBegin(false);
    }
    addRoute("/reset",
             [](AsyncWebServerRequest *request)
             {
                 AsyncWebServerResponse *response =
                     request->beginResponse(200);
                 request->send(response);

                 delay(111);
                 ESP.restart();
             });
    addRoute("/format",
             [](AsyncWebServerRequest *request)
             {
                 AsyncWebServerResponse *response =
                     request->beginResponse(200);
                 request->send(response);

                 delay(111);
                 nvs_flash_erase(); // erase the NVS partition.
                 nvs_flash_init();  // initialize the NVS partition.
                 ESP.restart();
             });
    addRoute("/status",
             [](AsyncWebServerRequest *request)
             {
                 DynamicJsonDocument _doc(1000);
                 JsonObject obj = _doc.to<JsonObject>();
                 obj["freeRam"] = ESP.getFreeHeap();
                 obj["waitForUpdate"] = waitForUpdate;
                 String ret;
                 serializeJson(obj, ret);

                 AsyncWebServerResponse *response =
                     request->beginResponse(200, String("application/json"), ret);
                 request->send(response);
             });

    uiBegin();

    if (waitForUpdate == true)
    {
        delay(1000 * 60 * 60);
    }
    button.setOnClick(
        [=]()
        {
            // Nhấn thả (click) để chuyển đến hiệu ứng tiếp theo
            box.nextEffect();
        });
    button.setOnLongClick(
        [=](uint32_t time)
        {
            // Nhấn thả lâu 3s (longclick) để bật tắt chế độ tự động chuyển

            box.setAutoChangeMode(!box.getAutoChangeMode());
        });
    button.setOnLongLongClick(
        [=](uint32_t time)
        {
            // Nhấn thả rất lâu 6s (longlongclick) để bật tắt microphone

            box.setOnMicrophone(!box.getOnMicrophone());
        });
    button.begin();
    box.begin();
    vTaskDelete(NULL);
}

void loop()
{
}
#endif