#pragma once
#include "render_layer.h"
#include "render_config.h"
#include "render_color_setting.h"
#include "render_microphone.h"

void render()
{
    setup_render_config();
    setup_render_layer();
    setup_color_setting();
    setup_microphone();
}