#pragma once
#include "render_layer.h"
#include "render_config.h"

void render()
{
    log_w("Befor render");
    setup_render_config();
    setup_render_layer();
    log_w("Affter render");

}