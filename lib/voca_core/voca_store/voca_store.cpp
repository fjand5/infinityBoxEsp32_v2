#include "voca_store.h"
VocaStore vocaStore;
bool VocaStore::mountSpiffs()
{
    log_d("==== Initializing SPIFFS ====\n");
    delay(111);
    if (!LITTLEFS.begin())
    {
        log_w("Can't mount SPIFFS, Try format\n");
        LITTLEFS.format();
        if (!LITTLEFS.begin())
        {
            log_w("Can't mount SPIFFS\n");
            log_e("==== Initialize SPIFFS failed ====\n");
            return false;
        }
        else
        {
            log_d("SPIFFS mounted\n");
            return true;
        }
    }
    else
    {
        log_d("SPIFFS mounted\n");
        return true;
    }
}

bool VocaStore::loadFileToContent()
{

    File cfg_file = LITTLEFS.open(CONFIG_FILE, "r");
    if (cfg_file)
    {
        // Mỗi dòng là một phần tử (một cặp key value) (key)=(value)
        while (cfg_file.available())
        {
            // cấp phát ở đây để tất cả phần tử đều là zero
            char *line = new char[MAX_CHAR_IN_LINE]();
            cfg_file.readBytesUntil('\n', line, MAX_CHAR_IN_LINE);

            std::string strLine(line);
            uint32_t splitPos = strLine.find("=");
            std::string key = strLine.substr(0, splitPos);
            std::string val = strLine.substr(splitPos + 1);

            storeContent[key] = val;
            // log_w("[%s: %s]", key.c_str(), val.c_str());
            delete line;
        }

        // String content = cfg_file.readString();
        // Mỗi dòng là một phần tử (một cặp key value) (key)=(value)
        // log_d("\n=======\n%s=======\n", content.c_str());
        // while (content.indexOf("\n") >= 0)
        // {
        //     String curLine = content.substring(0, content.indexOf("\n"));
        //     String key = curLine.substring(0, content.indexOf("="));
        //     String value = curLine.substring(content.indexOf("=") + 1);
        //     storeContent[key] = value;
        //     content.remove(0, curLine.length() + 1);
        // }

        semStoreContent = xSemaphoreCreateBinary();
        xSemaphoreGive(semStoreContent);
        cfg_file.close();

        return true;
    }
    else
    {
        // create file if not exist
        LITTLEFS.open(CONFIG_FILE, "a");
    }
}
VocaStore::VocaStore()
{
}
void VocaStore::begin()
{

    if (!mountSpiffs())
    {
        return;
    }
    loadFileToContent();
    semSpiffs = xSemaphoreCreateBinary();
    xSemaphoreGive(semSpiffs);

    vocaStatus.setStatus(Status_Store_Initialized);
    ready();
}
bool VocaStore::checkValidKey(std::string key)
{
 
    if (key.find("*") == 0                     // system key
        || key.find("=") != std::string::npos  // invalid key
        || key.find("\n") != std::string::npos // invalid key
    )
        return false;
    return true;
}
bool VocaStore::checkValidValue(std::string value)
{
    if (value.find("=") != std::string::npos     // invalid value
        || value.find("\n") != std::string::npos // invalid value
    )
        return false;
    return true;
}
void VocaStore::setValue(std::string key, std::string value, const bool save)
{

    // log_d("Setting Value: key: %s; value: %s\n", key.c_str(), value.c_str());
    bool isNoChange = false;
    if (checkKey(key))
    {
        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {

            isNoChange = storeContent[key] == value;
            xSemaphoreGive(semStoreContent);
        }
    }
    if (!isNoChange)
    {
        if (!checkValidKey(key) || !checkValidValue(value))
        {
            return;
        }
        // log_d("checked ValidKey Value: key: %s; value: %s\n", key.c_str(), value.c_str());

        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            storeContent[key] = value;
            xSemaphoreGive(semStoreContent);
        }
    }
    else
    {
        log_d("Nothing change!!!\n");
    }

    EventBusData *eventBusData = new EventBusData;
    strcpy(eventBusData->key,key.c_str());
    strcpy(eventBusData->val,value.c_str());
    vocaEventBus.executeEventBus(VOCA_STORE_NAME, 0, (void *)eventBusData, sizeof(EventBusData));
    delete eventBusData;

    // dữ liệu đã được copy nên có thể xóa
    // nếu không yêu cầu lưu vào flash hoặc giá trị như cũ
    if (
        !save ||
        isNoChange)
    {
        return;

    }
    updateStore();
};
bool VocaStore::updateStore()
{
    if (xSemaphoreTake(semSpiffs, portMAX_DELAY) == pdTRUE)
    {
    REOPEN:
        File cfg_file = LITTLEFS.open(CONFIG_FILE, "w");
        if (!cfg_file)
        {
            cfg_file.close();
            delay(100);
            log_e("Can't open file, reopening...");
            LITTLEFS.end();
            LITTLEFS.begin();
            goto REOPEN;
        }
        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            for (std::pair<std::string, std::string> e : storeContent)
            {
                std::string k = e.first;
                std::string v = e.second;
                cfg_file.printf("%s=%s\n", k.c_str(), v.c_str());
                // log_w("[%s: %s]", k.c_str(), v.c_str());
            }
            xSemaphoreGive(semStoreContent);
        }

        cfg_file.close();
        xSemaphoreGive(semSpiffs);
        return true;
    }
    return false;
}
void VocaStore::addStoreChangeEvent(EventBusFunction cb, void *prams)
{
    vocaEventBus.addEventBus(VOCA_STORE_NAME, cb,
                             prams, true);
}

bool VocaStore::checkKey(std::string key)
{
    if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
    {
        bool ret = storeContent.find(key) != storeContent.end();
        xSemaphoreGive(semStoreContent);
        return ret;
    }
    return false;
}

// uint32_t VocaStore::getValueSize(std::string key)
// {
//     if (checkKey(key))
//     {
//         if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
//         {
//             std::string _key(key);
//             std::string ret = storeContent[_key];
//             xSemaphoreGive(semStoreContent);
//             return ret.length();
//         }
//     }
//     else
//     {
//         return 0;
//     }
// };
std::string VocaStore::getValue(std::string key, std::string def, bool createIfNotExist, bool save)
{
    if (!checkValidKey(key))
        return "";
    if (checkKey(key))
    {
        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            std::string value = storeContent[key];
            xSemaphoreGive(semStoreContent);
            return value;
        }
    }
    else
    {
        if (createIfNotExist)
        {
            setValue(key, def, save);
        }
        return def;
    }
}
void VocaStore::readValueToObject(std::string key, JsonObject objectValue, std::string def, bool createIfNotExist)
{
    if (!checkKey(key))
    {
        return;
    }
    if (!checkValidKey(key))
    {

        return;
    }
    std::string value = getValue(key, def, createIfNotExist);
    objectValue[key] = value;
}
// uint32_t VocaStore::getStoreSize()
// {
//     uint32_t ret = 0;
//     if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
//     {
//         for (std::pair<std::string, std::string> e : storeContent)
//         {
//             std::string k = e.first;
//             if (k.find("*") == 0)
//                 continue;
//             std::string v = e.second;
//             std::string line = k + "=" + v + "\n";
//             ret += line.length();
//         }
//         xSemaphoreGive(semStoreContent);
//     }
//     return ret;
// };

std::string VocaStore::getStore()
{
    std::string storeData;
    if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
    {
        for (std::pair<std::string, std::string> e : storeContent)
        {
            std::string k = e.first;
            if (k.find("*") == 0)
                continue;
            std::string v = e.second;
            std::string line = k + "=" + v + "\n";
            storeData += line;
        }
        xSemaphoreGive(semStoreContent);
    }
    return storeData;
}
void VocaStore::readStore(JsonObject objectValues)
{
    if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
    {
        for (std::pair<std::string, std::string> e : storeContent)
        {
            std::string k = e.first;
            if (k.find("*") == 0)
                continue;
            std::string v = e.second;
            objectValues[k] = v;
        }
        xSemaphoreGive(semStoreContent);
    }
}
// char *VocaStore::createBuffer(const char *value)
// {

//     uint32_t curLen = strlen(value);
//     if (curLen > maxLengthOfValue)
//     {
//         maxLengthOfValue = curLen;
//     }
//     return new char[maxLengthOfValue + 1]();
// };