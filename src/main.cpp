#include <Arduino.h>
#include "voca_core.h"
#include "render/render.h"
#include "button/button.h"
#include "box/box.h"

void setup(void)
{
  log_w("main starting: %d", xPortGetCoreID());

  delay(555);
  setup_box();
  setup_button();
  setup_voca();
  render();
  vTaskDelete(NULL);
}

void loop(void)
{
}