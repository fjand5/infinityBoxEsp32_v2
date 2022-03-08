#include <Arduino.h>
#include "voca_core.h"
#include "render/render.h"
#include "controller.h"

void setup(void)
{
  Serial.begin(115200);
  delay(111);
  log_w("main starting: %d", xPortGetCoreID());
  settupSystem();
  setup_voca();

  render();

  std::string compile_date(__TIME__ " " __DATE__);
  vocaStore.setValue("_version", compile_date, true);

  std::string value = vocaStore.getValue("_countBoot", "0");
  uint32_t count = atoi(value.c_str());
  vocaStore.setValue("_countBoot", toString(count), true);

  // vTaskDelete(NULL);
}

void loop(void)
{
  static uint32_t lastFreeRam = ESP.getFreeHeap();
  if (ESP.getFreeHeap() != lastFreeRam)
  {
    log_e("Free Ram: %d", ESP.getFreeHeap());
    lastFreeRam = ESP.getFreeHeap();
  }
  delay(5000);
}
