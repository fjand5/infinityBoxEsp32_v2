#include <Arduino.h>
#include "voca_core.h"
// #include "render/render.h"
// #include "button/button.h"
// #include "box/box.h"

void setup(void)
{
  log_w("main starting: %d", xPortGetCoreID());
  // setup_box();
  // setup_button();
  setup_voca();
  // render();
  const char compile_date[] = __TIME__ " " __DATE__;
  // vocaStore.setValue("_version",compile_date);
  vTaskDelete(NULL);
}

void loop(void)
{
}

