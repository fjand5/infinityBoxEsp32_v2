#include "ui.h"
void uiBegin()
{
  addRoute("/",
           [](AsyncWebServerRequest *request)
           {
             AsyncWebServerResponse *response =
                 request->beginResponse_P(200,
                                          String("text/html"),
                                          (const uint8_t *)index_html,
                                          index_html_length,
                                          NULL);
             response->addHeader("Content-Encoding", "gzip");
             request->send(response);
           });

  addRoute("/js/app.js",
           [](AsyncWebServerRequest *request)
           {
             AsyncWebServerResponse *response =
                 request->beginResponse_P(200,
                                          String("application/javascript"),
                                          (const uint8_t *)app_js,
                                          app_js_length,
                                          NULL);
             response->addHeader("Content-Encoding", "gzip");
             request->send(response);
           });
  addRoute("/css/index.css",
           [](AsyncWebServerRequest *request)
           {
             AsyncWebServerResponse *response =
                 request->beginResponse_P(200,
                                          String("text/css"),
                                          (const uint8_t *)index_css,
                                          index_css_length,
                                          NULL);
             response->addHeader("Content-Encoding", "gzip");
             request->send(response);
           });
  addRoute("/favicon_io/favicon.ico",
           [](AsyncWebServerRequest *request)
           {
             AsyncWebServerResponse *response =
               request->beginResponse_P(200,
                                        String("image/vnd.microsoft.icon"),
                                        (const uint8_t *)favicon_ico,
                                        favicon_ico_length,
                                        NULL);
           response->addHeader("Content-Encoding", "gzip");
           request->send(response);
           });
}