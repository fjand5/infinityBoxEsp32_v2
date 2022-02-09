#include "voca_eventbus.h"
VocaEventBus vocaEventBus;
VocaEventBus::VocaEventBus(/* args */)
{

    esp_event_loop_create(&eventBusArgs, &eventBusHandle);
}

int32_t VocaEventBus::addEventBus(esp_event_handler_t cbEventBus)
{
    esp_event_handler_register_with(
        eventBusHandle,
        VOCA_EVENTBUS_NAME,
        idAutoIncrease++,
        cbEventBus,
        NULL);
    return idAutoIncrease;
};

void VocaEventBus::executeEventBus(int32_t id,
                                   void *data,
                                   size_t data_size)
{
    esp_event_post_to(
        eventBusHandle,
        VOCA_EVENTBUS_NAME,
        id,
        data,
        data_size,
        portMAX_DELAY);
};
VocaEventBus::~VocaEventBus()
{
}
