#pragma once

#include "voca_env.h"
#include "voca_webserver/voca_webserver.h"

void setupSystem(){
   vocaWebserver.addHttpApi("/reset",[](){
        log_w("Reset system");
        vocaWebserver.send(200);
        delay(500); // chờ send thành công.
        ESP.restart();
    });
}