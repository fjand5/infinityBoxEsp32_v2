#pragma once
#include "voca_env.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <functional>
#include "voca_websocket.h"
#include "voca_webserver/voca_webserver.h"

#include <map>
#include <list>
String renderData;
SemaphoreHandle_t renderData_sem;
typedef std::function <void (String key, String value)>ComponentEvent;
std::map<String, ComponentEvent> componentEvents;
void setOnEvents(String key, ComponentEvent cb)
{
  componentEvents[key] = cb;
}
void setupRender()
{
  renderData_sem = xSemaphoreCreateBinary();
  xSemaphoreGive(renderData_sem);
  vocaWebserver.addHttpApi("/render", []()
             { vocaWebserver.send_P(200, "application/json", renderData.c_str()); });
  setOnWSTextIncome([](JsonObject obj)
                    {
                      for (std::pair<String, ComponentEvent> e : componentEvents)
                      {
                        String k = e.first;
                        ComponentEvent cb = e.second;
                        if (obj["espKey"] == k)
                        {
                          cb(k, obj["espValue"]);
                        }
                      }
                    });
}
void renderComponent(String compt, String tab, String espKey, String props)
{
  if (xSemaphoreTake(renderData_sem, portMAX_DELAY) == pdTRUE)
  {
    DynamicJsonDocument docRender(20000);
    DeserializationError err = deserializeJson(docRender, renderData);
    
    renderData = "";
    JsonArray arrayRender;
    if (err)
    {
      arrayRender = docRender.to<JsonArray>();
    }
    else
    {
      arrayRender = docRender.as<JsonArray>();
    }

    JsonObject comptObj = arrayRender.createNestedObject();
    comptObj["type"] = compt;
    comptObj["tab"] = tab;
    comptObj["espKey"] = espKey;
    comptObj["props"] = serialized(props);

    serializeJson(docRender, renderData);
    xSemaphoreGive(renderData_sem);
  }
}

/*
option.span : số cột component chiếm
  option.span.xs (<768px)
  option.span.sm (>=768px)
  option.span.md (>=992px)
  option.span.lg (>=1200)
  option.span.xl (>=1920px)
option.offset : số cột component dịch sang phải (những components phía sau cũng bị dịch theo)
option.pull : di chuyển component sang phải (những components khác KHÔNG bị dịch theo)
option.push : di chuyển component sang trái
*/
void renderInput(String tab, String espKey, String option, ComponentEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspInput", tab, espKey, option);
}
void renderSlider(String tab, String espKey, String option, ComponentEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspSlider", tab, espKey, option);
}
void renderSwitch(String tab, String espKey, String option, ComponentEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspSwitch", tab, espKey, option);
}
void renderButton(String tab, String espKey, String option, ComponentEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspButton", tab, espKey, option);
}
void renderColorPicker(String tab, String espKey, String option, ComponentEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspColorPicker", tab, espKey, option);
}
void renderSelect(String tab, String espKey, String option, ComponentEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspSelect", tab, espKey, option);
}
// void renderInputText(String tab, String key, String name, String option, EventFunc event = NULL){
//   addEvent(key,event);
//   renderComponent("input-text", tab, key, name, option);
// }
// void renderPassword(String tab, String key, String name, String option, EventFunc event = NULL){
//   addEvent(key,event);
//   renderComponent("password", tab, key, name, option);

// }
