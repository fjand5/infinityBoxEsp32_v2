#include "web.h"
#include "CaptivePortal.h"

AsyncWebServer asyncWebServer(80);
HTTPUpdateServer httpUpdater;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
void addRoute(String uri, ArRequestHandlerFunction handler)
{
    asyncWebServer.on(uri.c_str(), HTTP_ANY, handler);
};
void webBegin(bool forceDefault)
{

    asyncWebServer.onNotFound(
        [](AsyncWebServerRequest *request)
        {
            if (request->method() == HTTP_OPTIONS)
            {
                request->send(200);
            }
            else
            {
                request->send(404);
            }
        });
  

    DefaultHeaders::Instance()
        .addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Expose-Headers", "*");

    xTaskCreatePinnedToCore(
        [](void *param)
        {
            // Chờ tất cả các hàm addRuote chạy xong
            httpUpdater.setup(&asyncWebServer);
            delay(5000);
            dnsServer.start(53, "*", WiFi.softAPIP());
            asyncWebServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
            asyncWebServer.begin();
            while (1)
            {
                dnsServer.processNextRequest();
                delay(1);
            }
        },
        PREF_WEB_NAME,
        4000,
        NULL,
        99,
        NULL,
        1);
}