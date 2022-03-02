#ifndef VOCA_STORE
#define VOCA_STORE
#define VOCA_STORE_NAME "voca_store"

#include "../voca_env.h"
#include "../voca_status/voca_status.h"
#include "../voca_eventbus/voca_eventbus.h"
#include "../voca_base/voca_base.h"
#include "FS.h"
#include "LITTLEFS.h"
#include <map>
#include <list>
#include <string>

#include <ArduinoJson.h>
extern VocaEventBus vocaEventBus;
class VocaStore: public VocaBase
{
private:
  std::map<std::string, std::string> storeContent;
  std::map<int32_t, std::string> keyIndex;
  SemaphoreHandle_t semSpiffs;
  SemaphoreHandle_t semStoreContent;
  bool mountSpiffs();
  bool loadFileToContent();
  bool checkValidKey(std::string key);
  bool checkValidValue(std::string value);

public:
  VocaStore();
  void begin();
  void setValue(std::string key, std::string value, bool save = false);
  bool updateStore();
  void addStoreChangeEvent(EventBusFunction cb, void *prams);
  bool checkKey(std::string key);
  // uint32_t getValueSize(std::string key);

  std::string getValue(std::string key, std::string def = "", bool createValueByDefault = true, bool save = true);
  void readValueToObject(std::string key, JsonObject objectValue, std::string def = "", bool createIfNotExist = true);

  // uint32_t getStoreSize();
  std::string getStore();
  void readStore(JsonObject objectValues);

};
extern VocaStore vocaStore;


#if 0
char* getUsername()
{
  char* username;
  if (!checkKey("*username"))
    return DEFAULT_USERNAME;
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    username = ConfigContent["*username"];
    xSemaphoreGive(configContent_sem);
  }
  return username;
}
void setUsername(char* username)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    ConfigContent["*username"] = username;
    xSemaphoreGive(configContent_sem);
  }
  saveConfigFile();
}
void setPassword(char* password)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    ConfigContent["*password"] = password;
    xSemaphoreGive(configContent_sem);
  }
  saveConfigFile();
}
char* getPassword()
{
  char* password;
  if (!checkKey("*password"))
    return DEFAULT_PASSWORD;
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    password = ConfigContent["*password"];
    xSemaphoreGive(configContent_sem);
  }
  return password;
}
bool Authentication(char* username, char* password)
{
  if (getUsername() == username && getPassword() == password)
    return true;
  return false;
}
#endif
#endif

// Lấy giá trị của Key
// Lấy toàn bộ file content