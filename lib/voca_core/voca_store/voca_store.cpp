#include "voca_store.h"
bool VocaStore::mountSpiffs()
{
    log_d("==== Initializing SPIFFS ====\n");
    delay(100);
    if (!SPIFFS.begin())
    {
        log_w("Can't mount SPIFFS, Try format\n");
        SPIFFS.format();
        if (!SPIFFS.begin())
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
    File cfg_file = SPIFFS.open(CONFIG_FILE, "r");
    if (cfg_file)
    {
        String content = cfg_file.readString();
        // Mỗi dòng là một phần tử (một cặp key value) (key)=(value)
        log_d("=======\n%s=======\n", content.c_str());
        while (content.indexOf("\n") >= 0)
        {
            String curLine = content.substring(0, content.indexOf("\n"));
            String key = curLine.substring(0, content.indexOf("="));
            String value = curLine.substring(content.indexOf("=") + 1);
            storeContent[key] = value;
            content.remove(0, curLine.length() + 1);
        }
        semConfigContent = xSemaphoreCreateBinary();
        xSemaphoreGive(semConfigContent);
        return true;
    }
    else
    {
        // create file if not exist
        SPIFFS.open(CONFIG_FILE, "a");
    }
    cfg_file.close();
}
VocaStore::VocaStore()
{
    if (!mountSpiffs())
    {
        return;
    }

    semSpiffs = xSemaphoreCreateBinary();
    xSemaphoreGive(semSpiffs);
    vocaStatus.setStatus(Status_Store_Initialized);
}
void VocaStore::setValue(const String key, const String value, const bool save = false)
{
    log_d("Setting Value: key: %s; value: %s\n", key.c_str(), value.c_str());
    bool isNoChange = storeContent[key] == value;
    if (!isNoChange)
    {
        if (key.startsWith("*") \       // system key
            || key.indexOf("=") >= 0 \  // invalid key
            || key.indexOf("\n") >= 0 \ //invalid key
            || value.indexOf("\n") >= 0)
        {
            return;
        }

        if (xSemaphoreTake(semConfigContent, portMAX_DELAY) == pdTRUE)
        {
            storeContent[key] = value;
            xSemaphoreGive(semConfigContent);
        }
    }
    else
    {
        log_d("Nothing change!!!\n");
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
};