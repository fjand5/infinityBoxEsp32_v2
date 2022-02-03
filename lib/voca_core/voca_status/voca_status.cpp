#include "voca_status.h"

VoCaStatus::VoCaStatus(/* args */)
{
    systemStatus = xEventGroupCreate();
}

VoCaStatus::~VoCaStatus()
{
}
void VoCaStatus::waitStatus(ModuleFlagReady_e status)
{
    xEventGroupWaitBits(systemStatus, 1<<status, pdFALSE, pdFALSE, portMAX_DELAY);
};
void VoCaStatus::waitAllStatus()
{
#define MODULE_FLAG_STATUS(name) \
    waitStatus(name);
    LIST_MODULE_FLAG_STATUS
#undef MODULE_FLAG_STATUS
};
void VoCaStatus::setStatus(ModuleFlagReady_e status)
{
    xEventGroupSetBits(systemStatus, 1<<status);
};
void VoCaStatus::clearStatus(ModuleFlagReady_e status)
{
    xEventGroupClearBits(systemStatus, 1<<status);
};

VoCaStatus vocaStatus;