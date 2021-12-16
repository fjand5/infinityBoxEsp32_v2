#include <Arduino.h>
#include "voca_core.h"
#include "render/render.h"
// #include "button.h"
#include "box/box.h"

void setup(void)
{
  log_w("main starting: %d", xPortGetCoreID());

  delay(555);
  setup_voca();
  // delay(5000);

  log_i("setup_voca");
  setup_box();
  log_i("setup_box");
  render();
  vTaskDelete(NULL);
}

void loop(void)
{
}