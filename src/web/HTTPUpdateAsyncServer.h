#ifndef __HTTP_UPDATE_SERVER_H
#define __HTTP_UPDATE_SERVER_H

#include <SPIFFS.h>
#include <StreamString.h>
#include <Update.h>
#include <ESPAsyncWebServer.h>

static const char serverIndex[] PROGMEM =
    R"(<!DOCTYPE html>
     <html lang='en'>
     <head>
         <meta charset='utf-8'>
         <meta name='viewport' content='width=device-width,initial-scale=1'/>
     </head>
     <body>
     <form method='POST' action='' enctype='multipart/form-data'>
         Firmware:<br>
         <input type='file' accept='.bin,.bin.gz' name='firmware'>
         <input type='submit' value='Update Firmware'>
     </form>
     <form method='POST' action='' enctype='multipart/form-data'>
         FileSystem:<br>
         <input type='file' accept='.bin,.bin.gz,.image' name='filesystem'>
         <input type='submit' value='Update FileSystem'>
     </form>
     </body>
     </html>)";
static const char successResponse[] PROGMEM =
    "<META http-equiv=\"refresh\" content=\"15;URL=/\">Update Success! Rebooting...";

class HTTPUpdateServer
{
public:
  HTTPUpdateServer(bool serial_debug = false)
  {
    // _serial_output = serial_debug;
    _server = NULL;
    // _username = emptyString;
    // _password = emptyString;
    // _authenticated = false;
  }

  void setup(AsyncWebServer *server)
  {
    setup(server, emptyString, emptyString);
  }

  void setup(AsyncWebServer *server, const String &path)
  {
    setup(server, path, emptyString, emptyString);
  }

  void setup(AsyncWebServer *server, const String &username, const String &password)
  {
    setup(server, "/update", username, password);
  }

  void setup(AsyncWebServer *server, const String &path, const String &username, const String &password)
  {

    _server = server;
    // _username = username;
    // _password = password;

    // handler for the /update form page
    _server->on(path.c_str(), HTTP_GET,
                [&](AsyncWebServerRequest *request)
                {
                  AsyncWebServerResponse *response =
                      request->beginResponse_P(200,
                                               PSTR("text/html"),
                                               (const uint8_t *)serverIndex,
                                               strlen_P(serverIndex),
                                               NULL);
                  request->send(response);
                });
    _server->on(
        "/update", HTTP_POST,
        [&](AsyncWebServerRequest *request)
        {
          shouldReboot = !Update.hasError();
          AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot ? successResponse : "FAIL");
          response->addHeader("Connection", "close");
          request->send(response);
          delay(1000);
          if (shouldReboot)
            ESP.restart(); },
        [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
        {
          if (!index)
          {
            if (!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000))
            {
              // Update.printError(Serial);
            }
          }
          if (!Update.hasError())
          {
            if (Update.write(data, len) != len)
            {
              // Update.printError(Serial);
            }
          }
          if (final)
          {
            if (Update.end(true))
            {
              // Serial.printf("Update Success: %uB\n", index + len);
            }
            else
            {
              // Update.printError(Serial);
            }
          }
        });
  }

protected:
  // void _setUpdaterError()
  // {
  //   if (_serial_output)
  //     Update.printError(Serial);
  //   StreamString str;
  //   Update.printError(str);
  //   _updaterError = str.c_str();
  // }

private:
  bool _serial_output;
  bool shouldReboot;
  AsyncWebServer *_server;
  // String _username;
  // String _password;
  // bool _authenticated;
  String _updaterError;
};

#endif