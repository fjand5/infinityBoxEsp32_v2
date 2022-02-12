#ifndef CONTROLLER
#define CONTROLLER

#include "render/render.h"
#include "control_button/control_button.h"
#include "box/real_box/real_box.h"
// #include "microphone/microphone.h"

void onTimerMode()
{
    box_setTimerRandomMode(true);
    controlButton.setLedMode(LedMode_FadeFast);
    vocaStore.setValue("rdmTmrMd", "true");
}
void offTimerMode()
{
    box_setTimerRandomMode(false);
    controlButton.setLedMode(LedMode_Blink);
    vocaStore.setValue("rdmTmrMd", "false");
}
void settupSystem()
{
    vocaStore.setOnReady(
        []()
        {
            realBox.begin();
            if (vocaStore.getValue("rdmTmrMd", "true") == "true")
            {
                onTimerMode();
            }
            else
            {
                offTimerMode();
            }
        });
    controlButton.begin();
    controlButton.setClickEvent(
        []()
        {
            box_randomModeAll();
        });
    controlButton.setDoubleClickEvent(
        []()
        {
            static bool lastState = true;
            if (lastState == true)
            {
                onTimerMode();
            }
            else
            {
                offTimerMode();
            }
            lastState = !lastState;
        });
}
#endif