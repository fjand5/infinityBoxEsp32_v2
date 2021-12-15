#pragma once
#include "voca_env.h"
#include "voca_dist.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include "voca_store.h"
#include "voca_auth.h"

WebServer server(80);
SemaphoreHandle_t http_request_sem;
typedef void (*Response)(void);
void comHeader()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.sendHeader("Access-Control-Expose-Headers", "*");
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
  server.sendHeader("Content-Encoding", "gzip");
  server.send_P(200, "text/html", index_html, index_html_length);
}
void setupWebserver()
{

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
                      server.sendHeader("Content-Encoding", "gzip");
                      server.send_P(200, "application/javascript", app_js, app_js_length);
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/fonts/element-icons.woff",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {
                      comHeader();
                      server.sendHeader("Content-Encoding", "gzip");
                      server.send_P(200, "application/javascript", font_woff, font_woff_length);
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.on("/static/favicon.ico",
                  []()
                  {
                    if (xSemaphoreTake(http_request_sem, portMAX_DELAY) == pdTRUE)
                    {
                      comHeader();
                      server.sendHeader("Content-Encoding", "gzip");
                      server.send_P(200, "application/javascript", favicon_ico, favicon_ico_length);
                      xSemaphoreGive(http_request_sem);
                    }
                  });
        server.begin();
        log_w("loopWebserver is running on core: %d", xPortGetCoreID());
        http_request_sem = xSemaphoreCreateBinary();
        xSemaphoreGive(http_request_sem);
        SET_FLAG(FLAG_WEBSERVER_READY);
        WAIT_FLAG_SET(FLAG_WEBSERVER_READY | FLAG_WEBSOCKET_READY);

        while (1)
        {
          server.handleClient();
          delay(20);
        }
      },
      "loopWebserver",
      100000,
      NULL,
      1,
      NULL,
      VOCA_CORE_CPU);
}