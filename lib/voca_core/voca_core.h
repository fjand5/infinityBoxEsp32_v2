#pragma once
#include "voca_status.h"
#include "voca_wifi.h"
#include "voca_webserver.h"
#include "voca_store.h"
#include "voca_system.h"
#include "voca_websocket.h"
#include "voca_render.h"

void setup_voca()
{
    log_i("settupStatus");
    settupStatus();
    log_i("setupStore");
    setupStore();
    log_i("setupWifi");
    setupWifi();
    log_i("setupWebserver");
    setupWebserver();
    log_i("setupWebSocket");
    setupWebSocket();
    log_i("setupSystem");
    setupSystem();
    log_i("setupRender");
    setupRender();
    
}