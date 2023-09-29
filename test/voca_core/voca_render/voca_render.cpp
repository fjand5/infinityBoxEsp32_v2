#include "voca_render.h"
VocaRender vocaRender;
VocaRender::VocaRender(/* args */)
{
}

void VocaRender::addComponentEvents(std::string key, ComponentEvent cb, void* param)
{
  std::string _key(key);
  ComponentEventParam componentEventParam = std::make_pair(cb,param);
  componentEvents[_key] = componentEventParam;
}

void VocaRender::renderComponent(std::string compt, std::string tab, std::string espKey, std::string props)
{
  if (xSemaphoreTake(semVocaRender, portMAX_DELAY) == pdTRUE)
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
    xSemaphoreGive(semVocaRender);
  }
}
void VocaRender::begin()
{
  semVocaRender = xSemaphoreCreateBinary();
  xSemaphoreGive(semVocaRender);
  vocaWebserver.addHttpApi(
      "/render",
      [this]()
      {
        vocaWebserver.send_P(200, "application/json", renderData.c_str());
      });
  vocaWebsocket.setWebsocketReceiveEvent(
      [this](JsonObject obj)
      {
        for (std::pair<std::string, ComponentEventParam> e : componentEvents)
        {
          std::string k = e.first;
          ComponentEventParam componentEventParam = e.second;
          ComponentEvent cb = componentEventParam.first;
          void* _param = componentEventParam.second;
          if (obj["espKey"] == k)
          {
            cb(k.c_str(), obj["espValue"].as<std::string>(), _param);
          }
        }
      });
}

void VocaRender::renderInput(std::string tab, std::string espKey, std::string option, ComponentEvent event, void* param)
{
  addComponentEvents(espKey, event, param);
  renderComponent("EspInput", tab, espKey, option);
}
void VocaRender::renderSlider(std::string tab, std::string espKey, std::string option, ComponentEvent event, void* param)
{
  addComponentEvents(espKey, event, param);
  renderComponent("EspSlider", tab, espKey, option);
}
void VocaRender::renderSwitch(std::string tab, std::string espKey, std::string option, ComponentEvent event, void* param)
{
  addComponentEvents(espKey, event, param);
  renderComponent("EspSwitch", tab, espKey, option);
}
void VocaRender::renderButton(std::string tab, std::string espKey, std::string option, ComponentEvent event, void* param)
{
  addComponentEvents(espKey, event, param);
  renderComponent("EspButton", tab, espKey, option);
}
void VocaRender::renderColorPicker(std::string tab, std::string espKey, std::string option, ComponentEvent event, void* param)
{
  addComponentEvents(espKey, event, param);
  renderComponent("EspColorPicker", tab, espKey, option);
}
void VocaRender::renderSelect(std::string tab, std::string espKey, std::string option, ComponentEvent event, void* param)
{
  addComponentEvents(espKey, event, param);
  renderComponent("EspSelect", tab, espKey, option);
}
VocaRender::~VocaRender()
{
}