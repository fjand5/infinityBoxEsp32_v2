#include <Arduino.h>
// #include "voca_core.h"
// #include "button.h"
#include "box/box.h"

void setup(void)
{
  delay(555);

  // setup_voca();
  // log_i("main is running on core: %d",xPortGetCoreID());
  setup_box();

  vTaskDelete(NULL);
}

void loop(void)
{
}