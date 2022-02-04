#pragma once

#include "voca_env.h"
#include "voca_status/voca_status.h"
#include "voca_wifi.h"
#include "voca_webserver.h"
#include "voca_store/voca_store.h"
#include "voca_system.h"
#include "voca_websocket.h"
#include "voca_render.h"
void setup_voca()
{
    // settupStatus();
    // setupStore();
    setupRender();
    setupWifi();
    setupWebserver();

    setupWebSocket();
    setupSystem();
    vocaStatus.waitAllStatus();
}