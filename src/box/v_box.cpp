#include "v_box.h"
VBox::VBox(uint16_t num_leds, uint8_t pin, neoPixelType type,
         uint8_t max_num_segments,
         uint8_t max_num_active_segments ) : WS2812FX(num_leds, pin, type,
                                                                               max_num_segments,
                                                                               max_num_active_segments)
{
}