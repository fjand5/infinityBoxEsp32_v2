#include "CaptivePortal.h"

CaptiveRequestHandler::CaptiveRequestHandler() {}
CaptiveRequestHandler::~CaptiveRequestHandler() {}

bool CaptiveRequestHandler::canHandle(AsyncWebServerRequest *request)
{
    request->addInterestingHeader("ANY");
    return true;
}

void CaptiveRequestHandler::handleRequest(AsyncWebServerRequest *request)
{
    AsyncWebServerResponse *response =
        request->beginResponse_P(200,
                                 String("text/html"),
                                 (const uint8_t *)index_html,
                                 index_html_length,
                                 NULL);
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}
