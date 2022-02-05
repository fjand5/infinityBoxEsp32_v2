#include "control_button_env.h"
#include <EasyButton.h>
#include <Arduino.h>
#include <SPIFFS.h>

typedef std::function<void(void)> ClickEvent;
typedef std::function<void(void)> DoubleClickEvent;

class ControlButton : public EasyButton
{
private:
    void resetFactory();

protected:
    ClickEvent clickEvent = NULL;
    DoubleClickEvent doubleClickEvent = NULL;

public:
    ControlButton(uint8_t pin);
    void setClickEvent(ClickEvent cbClickEvent);
    void begin();
    ~ControlButton();
};

extern ControlButton controlButton;
// void doubleClick()
// {
//     log_d(" doubleClick");
//     lastClickTime = 0;
// }