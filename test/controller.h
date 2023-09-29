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
    // controlButton.setLedMode(LedMode_FadeFast);
    vocaStore.setValue("rndTmrMd", "true");
}
void offTimerMode()
{
    box_setTimerRandomMode(false);
    // controlButton.setLedMode(LedMode_Blink);
    vocaStore.setValue("rndTmrMd", "false");
}
void setMicGain(std::string gain)
{
    microphone.setMicGain(atoi(gain.c_str()));
    vocaStore.setValue("micGain", gain);
}
void setMicTakeBeat(std::string beat)
{
    microphone.setTakeBeat(atoi(beat.c_str()));
    vocaStore.setValue("micBeat", beat);
}
void setMusicEffect(std::string effect)
{
    musicBox.setEffect(atoi(effect.c_str()));
    vocaStore.setValue("msEff", effect);
}
void settupSystem()
{
    vocaStore.setOnReady(
        []()
        {
            microphone.begin();
            realBox.begin();

            long gain = atoi(vocaStore.getValue("micGain","50").c_str());
            long beat = atoi(vocaStore.getValue("micBeat","50").c_str());
            microphone.setMicGain(gain);
            microphone.setMicGain(beat);
            int effect = atoi(vocaStore.getValue("msEff","0").c_str());
            musicBox.setEffect(effect);

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
    // controlButton.begin();
    // controlButton.setClickEvent(
        // []()
        // {
        //     box_randomModeAll();
        // });
    // controlButton.setDoubleClickEvent(
        // []()
        // {
        //     static bool lastState = true;
        //     if (lastState == true)
        //     {
        //         onTimerMode();
        //     }
        //     else
        //     {
        //         offTimerMode();
        //     }
        //     lastState = !lastState;
        // });
}
#endif