#ifndef CONTROLLER
#define CONTROLLER
#include "box/box_controller.h"

#include "render/render.h"
#include "control_button/control_button.h"
#include "microphone/microphone.h"
// #include "box/real_box/real_box.h"
// void onMusicMode()
// {
//     box_setTimerRandomMode(true);
//     vocaStore.setValue("msMd", "true");
// }
void onTimerMode()
{
    box_setTimerRandomMode(true);
    controlButton.setLedMode(LedMode_FadeFast);
    vocaStore.setValue("rndTmrMd", "true");
}
void offTimerMode()
{
    box_setTimerRandomMode(false);
    controlButton.setLedMode(LedMode_Blink);
    vocaStore.setValue("rndTmrMd", "false");
}
void settupSystem()
{
    vocaStore.setOnReady(
        []()
        {
            microphone.begin();
            realBox.begin();

            std::string value = vocaStore.getValue("rndTmrMd", "true");
            if (!value.compare("true"))
            {
                onTimerMode();
            }
            else
            {
                offTimerMode();
            }
            value = vocaStore.getValue("rndClTm", "true");
            box_setTimerRandomColor(!value.compare("true"));
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