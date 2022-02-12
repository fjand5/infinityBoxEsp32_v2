#ifndef CONTROL_BUTTON
#define CONTROL_BUTTON
#include "control_button_env.h"

#include <EasyButton.h>
#include <Arduino.h>


#include "FS.h"
#include "SPIFFS.h" // Dùng cho việc format factory

typedef std::function<void(void)> ClickEvent;
typedef std::function<void(void)> DoubleClickEvent;

typedef enum
{
    LedMode_Blink,
    LedMode_Off,
    LedMode_On,
    LedMode_FadeFast,
    LedMode_FadeSlow
} LedMode;
class ControlButton : public EasyButton
{
private:
    static void resetFactory();
    ClickEvent clickEvent = NULL;
    DoubleClickEvent doubleClickEvent = NULL;
    LedMode ledMode;

public:
    ControlButton(uint8_t pin);
    void setLedMode(LedMode mode);
    void setClickEvent(ClickEvent cbClickEvent);
    void setDoubleClickEvent(DoubleClickEvent cbDoubleClickEvent);
    void begin();
    ~ControlButton();
    friend class ControlButton_Handle;
};

class ControlButton_Handle : public ControlButton
{
public:
    void ledHandle();
    void buttonHandle();
};

extern ControlButton controlButton;
// void doubleClick()
// {
//     log_d(" doubleClick");
//     lastClickTime = 0;
// }
#endif