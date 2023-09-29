#pragma once
#include "ESPAsyncWebServer.h"
#include "../ui/dist.h"

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
    CaptiveRequestHandler();
    ~CaptiveRequestHandler();

    bool canHandle(AsyncWebServerRequest *request);

    void handleRequest(AsyncWebServerRequest *request);
};
