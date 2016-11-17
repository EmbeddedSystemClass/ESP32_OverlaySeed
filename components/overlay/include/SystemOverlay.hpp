#ifndef __SYSTEM_OVERLAY_HPP
#define __SYSTEM_OVERLAY_HPP

#ifdef __cplusplus
extern "C"{
#endif

#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"

#ifdef __cplusplus
}
#endif

class SystemOverlay{
public:
    bool Init();

    static SystemOverlay* Instance();
private:
    SystemOverlay();

    static SystemOverlay* _me;
    static esp_err_t event_handler(void *ctx, system_event_t *event);
};

#endif