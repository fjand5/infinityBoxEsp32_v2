#pragma once
#include "voca_env.h"
#include "voca_dist.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include "voca_store/voca_store.h"
#include "voca_auth.h"
#include "voca_update.h"
#include "voca_status/voca_status.h"

WebServer server(80);
SemaphoreHandle_t http_request_sem;
typedef void (*Response)(void);
void comHeader()
{
  server.sendHeader(F("Access-Control-Allow-Origin"), "*");
  server.sendHeader(F("Access-Control-Allow-Methods"), "PUT,POST,GET,OPTIONS");
  server.sendHeader(F("Access-Control-Allow-Headers"), "*");
  server.sendHeader(F("Access-Control-Expose-Headers"), "*");
}
void addHttpApi(String url, Response response)
{
  if (url.startsWith("/"))
    url = url.substring(1);
  server.on(String("/api/") + url, [response]()
            {
              if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
              {
                comHeader();
                if (server.method() == HTTP_OPTIONS)
                {
                  server.send(200);
                  xSemaphoreGive(http_request_sem);
                  return;
                }
                String token = server.header("Authorization");
                token.replace("Bearer ", "");
                if (check_auth_jwt(token))
                {
                  String bearerHeader = String("Bearer ") + create_auth_jwt();
                  server.sendHeader("Authorization", bearerHeader);
                  response();
                }
                else
                {
                  server.send(401);
                }
                xSemaphoreGive(http_request_sem);
              }
            });
}

void handleIndex()
{
  comHeader();
#ifdef USE_DATA_FROM_FILE
  File index_html = SPIFFS.open("/index.html.gz", "r");
  server.streamFile(index_html, "text/html");
  index_html.close();
#else
  server.sendHeader("Content-Encoding", "gzip");
  server.send_P(200, "text/html", index_html, index_html_length);
#endif
}
void setupWebserver()
{
  vocaStatus.waitStatus(Status_SetupWifi_Done);
  xTaskCreatePinnedToCore(
      [](void *param)
      {
        server.on("/", handleIndex);
        server.on("/checkToken",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {

                      comHeader();
                      if (server.method() == HTTP_OPTIONS)
                      {
                        server.send(200);
                        xSemaphoreGive(http_request_sem);
                        return;
                      }
                      String token = server.header("Authorization");
                      token.replace("Bearer ", "");
                      if (check_auth_jwt(token))
                      {
                        String bearerHeader = String("Bearer ") + create_auth_jwt();
                        server.sendHeader("Authorization", bearerHeader);
                        server.send(200);
                      }
                      else
                      {
                        server.send(401);
                      }
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/login",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {

                      comHeader();
                      if (server.method() == HTTP_OPTIONS)
                      {
                        server.send(200);
                        xSemaphoreGive(http_request_sem);
                        return;
                      }
                      log_d("getUsername: %s; getPassword: %s;", getUsername().c_str(), getPassword().c_str());
                      if (server.authenticate(getUsername().c_str(), getPassword().c_str()))
                      {
                        String bearerHeader = String("Bearer ") + create_auth_jwt();
                        server.sendHeader("Authorization", bearerHeader);

                        server.send(200);
                      }
                      else
                      {
                        server.send(401);
                      }
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/changePassword",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {

                      comHeader();
                      if (server.method() == HTTP_OPTIONS)
                      {
                        server.send(200);
                        xSemaphoreGive(http_request_sem);
                        return;
                      }
                      String token = server.header("Authorization");
                      token.replace("Bearer ", "");
                      if (check_auth_jwt(token))
                      {
                        String bearerHeader = String("Bearer ") + create_auth_jwt();
                        server.sendHeader("Authorization", bearerHeader);
                        String arg = server.arg(0);

                        DynamicJsonDocument _doc(258);
                        deserializeJson(_doc, arg);
                        JsonObject obj = _doc.as<JsonObject>();
                        String password = obj["password"];
                        String newPassword = obj["newPassword"];
                        if (getPassword() == password)
                        {
                          setPassword(newPassword);
                          server.send(200);
                        }
                        else
                        {
                          server.send(400);
                        }
                      }
                      else
                      {
                        server.send(401);
                      }
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/js/app.js",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {
                      comHeader();

#ifdef USE_DATA_FROM_FILE
                      File app_js = SPIFFS.open("/app.js.gz", "r");
                      server.streamFile(app_js, "application/javascript");
                      app_js.close();
#else
                server.sendHeader("Content-Encoding", "gzip");
                server.send_P(200, "application/javascript", app_js, app_js_length);
#endif
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/fonts/element-icons.woff",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {
                      comHeader();

#ifdef USE_DATA_FROM_FILE
                      File font_woff = SPIFFS.open("/element-icons.woff.gz", "r");
                      server.streamFile(font_woff, "application/javascript");
                      font_woff.close();
#else
                server.sendHeader("Content-Encoding", "gzip");
                server.send_P(200, "application/javascript", font_woff, font_woff_length);
#endif
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/static/favicon.ico",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {
                      comHeader();
#ifdef USE_DATA_FROM_FILE
                      File favicon_ico = SPIFFS.open("/favicon.ico.gz", "r");
                      server.streamFile(favicon_ico, "application/javascript");
                      favicon_ico.close();
#else
                server.sendHeader("Content-Encoding", "gzip");
                server.send_P(200, "application/javascript", favicon_ico, favicon_ico_length);
#endif
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        setupUpdate();

        server.begin();
        log_w("loopWebserver is running on core: %d", xPortGetCoreID());
        http_request_sem = xSemaphoreCreateBinary();
        xSemaphoreGive(http_request_sem);
        vocaStatus.setStatus(Status_WebServer_Ready);
        vocaStatus.waitStatus(Status_WebSocket_Ready);

        while (1)
        {
          server.handleClient();
          delay(20);
        }
      },
      "loopWebserver",
      4096,
      NULL,
      1,
      NULL,
      VOCA_CORE_CPU);
}