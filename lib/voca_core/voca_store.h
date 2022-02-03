#pragma once
#include "voca_env.h"
#define DEFAULT_USERNAME "admin"
#define DEFAULT_PASSWORD "12345678"
#define CONFIG_FILE "/config.txt"
#include "FS.h"
#include "SPIFFS.h"
#include <map>
#include <list>
#include <WS2812FX.h>
#include "voca_status/voca_status.h"

void saveConfigFile();
void setValue(String key, String value, bool save = true);
std::map<String, String> ConfigContent;
typedef void (*configChangeCallback)(String, String, void *);
std::list<std::pair<configChangeCallback, void *>> onStoreChanges;
SemaphoreHandle_t spiffs_sem;
SemaphoreHandle_t configContent_sem;
void setOnStoreChange(void (*func)(String key, String value, void *_p), void *p)
{
  onStoreChanges.push_front(std::make_pair(func,p));
}
// Mỗi dòng là một phần tử (một cặp key value) (key):(value)\n
void loadFileIntoConfig(String content)
{
  log_d("%s", content.c_str());
  configContent_sem = xSemaphoreCreateBinary();
  while (content.indexOf("\n") >= 0)
  {
    String curLine = content.substring(0, content.indexOf("\n"));
    String key = curLine.substring(0, content.indexOf("="));
    String value = curLine.substring(content.indexOf("=") + 1);
    ConfigContent[key] = value;
    content.remove(0, curLine.length() + 1);
  }
  xSemaphoreGive(configContent_sem);
}
// Kiểm tra key có tồn tại không
bool checkKey(String key)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    bool ret = ConfigContent.find(key) != ConfigContent.end();
    xSemaphoreGive(configContent_sem);
    return ret;
  }
  return false;
}

String getUsername()
{
  String username;
  if (!checkKey("*username"))
    return DEFAULT_USERNAME;
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    username = ConfigContent["*username"];
    xSemaphoreGive(configContent_sem);
  }
  return username;
}
void setUsername(String username)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    ConfigContent["*username"] = username;
    xSemaphoreGive(configContent_sem);
  }
  saveConfigFile();
}
void setPassword(String password)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    ConfigContent["*password"] = password;
    xSemaphoreGive(configContent_sem);
  }
  saveConfigFile();
}
String getPassword()
{
  String password;
  if (!checkKey("*password"))
    return DEFAULT_PASSWORD;
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    password = ConfigContent["*password"];
    xSemaphoreGive(configContent_sem);
  }
  return password;
}
bool Authentication(String username, String password)
{
  if (getUsername() == username && getPassword() == password)
    return true;
  return false;
}

// Lấy giá trị của Key
String getValue(String key, String def = "", bool setDefaultTokey = true)
{
  if (key.startsWith("*"))
    return "";
  if (checkKey(key))
  {
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      String ret = ConfigContent[key];
      xSemaphoreGive(configContent_sem);
      return ret;
    }
  }
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    return def;
  }
}
void getValueByObject(String key, JsonObject objectValue, String def = "", bool setDefaultTokey = true)
{
  if (key.startsWith("*"))
    return;
  String value = getValue(key, def, setDefaultTokey);
  objectValue[key] = value;
}
char *getValueByCStr(String key, String def = "", bool setDefaultTokey = true)
{
  char *ret;

  if (key.startsWith("*"))
    return "";
  if (checkKey(key))
  {
    String tmp;
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      tmp = ConfigContent[key];
      xSemaphoreGive(configContent_sem);
    }
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    String tmp = def;
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
}
// Lấy toàn bộ file content
String getValuesByString()
{
  String ret = "";
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    for (std::pair<String, String> e : ConfigContent)
    {
      String k = e.first;
      if (k.startsWith("*"))
        continue;
      String v = e.second;
      ret += k + "=" + v + "\n";
    }
    xSemaphoreGive(configContent_sem);
  }
  return ret;
}
void getValuesByObject(JsonObject objectValues)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    for (std::pair<String, String> e : ConfigContent)
    {
      String k = e.first;
      if (k.startsWith("*"))
        continue;
      String v = e.second;
      objectValues[k] = v;
    }
    xSemaphoreGive(configContent_sem);
  }
}
// Gán giá trị cho key
void setValue(String key, String value, bool save)
{
  log_d("setValue: key: %s; value: %s", key.c_str(), value.c_str());
  bool noChange = ConfigContent[key] == value;
  if (!noChange)
  {
    if (key.startsWith("*") || key.indexOf("=") >= 0 || key.indexOf("\n") >= 0 || value.indexOf("\n") >= 0)
      return;

    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      ConfigContent[key] = value;
      xSemaphoreGive(configContent_sem);
    }
  }

  for (auto onStoreChange = onStoreChanges.begin();
       onStoreChange != onStoreChanges.end();
       ++onStoreChange)
  {
      onStoreChange->first(key, value, onStoreChange->second);
  }

  // nếu không yêu cầu lưu vào flash hoặc giá trị như cũ
  if (!save || noChange)
  {
    return;
  }
  saveConfigFile();
}

void saveConfigFile()
{
  if (xSemaphoreTake(spiffs_sem, portMAX_DELAY) == pdTRUE)
  {
  REOPEN:
    File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
    if (!cfg_file)
    {
      cfg_file.close();
      delay(100);
      log_e("can't open file, reopening...");
      SPIFFS.end();
      SPIFFS.begin();
      goto REOPEN;
    }
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      for (std::pair<String, String> e : ConfigContent)
      {
        String k = e.first;
        String v = e.second;
        cfg_file.print(k + "=" + v + "\n");
      }
      xSemaphoreGive(configContent_sem);
    }

    cfg_file.close();
    xSemaphoreGive(spiffs_sem);
  }
}
// Khởi tạo
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    log_w("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        log_w("- failed to open directory\n");
        return;
    }
    if(!root.isDirectory()){
        log_w(" - not a directory\n");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            log_w("  DIR : ");
            log_w("%s",file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            log_w("  FILE: ");
            log_w("%s",file.name());
            log_w("\tSIZE: ");
            log_w("%d\n",file.size());
        }
        file = root.openNextFile();
    }
}
void setupStore()
{
  spiffs_sem = xSemaphoreCreateBinary();
  log_w("Initialize SPIFFS");
  delay(100);
  if (!SPIFFS.begin())
  {
    log_d("Can't mount SPIFFS, Try format");
    SPIFFS.format();
    if (!SPIFFS.begin())
    {
      log_d("Can't mount SPIFFS");
      return;
    }
    else
    {
      log_d("SPIFFS mounted");
      xSemaphoreGive(spiffs_sem);
    }
  }
  else
  {
    log_d("SPIFFS mounted ");
    listDir(SPIFFS, "/", 9);
    xSemaphoreGive(spiffs_sem);
  }
  if (xSemaphoreTake(spiffs_sem, portMAX_DELAY) == pdTRUE)
  {
    File cfg_file = SPIFFS.open(CONFIG_FILE, "r");
    if (cfg_file)
    {
      String tmp = cfg_file.readString();
      loadFileIntoConfig(tmp);
    }
    else
    {
      SPIFFS.open(CONFIG_FILE, "a");
    }
    cfg_file.close();
    xSemaphoreGive(spiffs_sem);
  }
  vocaStatus.setStatus(Status_Store_Initialized);
}

void loopConfig()
{
}
