#pragma once
#include "../voca_env.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <functional>
#include "../voca_websocket/voca_websocket.h"
#include "../voca_webserver/voca_webserver.h"
#include <map>
#include <list>
#include <string>

typedef std::function<void(std::string key, std::string value, void *param)> ComponentEvent;
typedef std::pair <ComponentEvent,void*> ComponentEventParam; 
class VocaRender
{
private:
  std::string renderData;
  SemaphoreHandle_t semVocaRender;
  std::map<std::string, ComponentEventParam> componentEvents;
  void addComponentEvents(std::string key, ComponentEvent cb, void *param);

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
  void renderComponent(std::string compt, std::string tab, std::string espKey, std::string props);

public:
  VocaRender();
  void begin();
  void renderInput(std::string tab, std::string espKey, std::string option, ComponentEvent event, void *param);
  void renderSlider(std::string tab, std::string espKey, std::string option, ComponentEvent event, void *param);
  void renderSwitch(std::string tab, std::string espKey, std::string option, ComponentEvent event, void *param);
  void renderButton(std::string tab, std::string espKey, std::string option, ComponentEvent event, void *param);
  void renderColorPicker(std::string tab, std::string espKey, std::string option, ComponentEvent event, void *param);
  void renderSelect(std::string tab, std::string espKey, std::string option, ComponentEvent event, void *param);
  ~VocaRender();
};
extern VocaRender vocaRender;
