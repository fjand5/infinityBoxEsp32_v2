#include <Arduino.h>
#include "voca_core.h"
#include "render/render.h"
// #include "button.h"
#include "box/box.h"

void setup(void)
{
  delay(555);

  setup_voca();
  log_i("setup_voca");
  delay(3000);
  setup_box();
  log_i("setup_box");
  setup_render();
  vTaskDelete(NULL);
}

void loop(void)
{
}