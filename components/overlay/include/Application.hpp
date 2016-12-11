#ifdef __cplusplus
extern "C"{
#endif

#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"

int app_main(void);

#ifdef __cplusplus
}
#endif

#include "SystemOverlay.hpp"

#ifdef WIFI_OVERLAY
#include "WIFIOverlay.hpp"
#endif

#ifdef GPIO_OVERLAY
#include "GPIOOverlay.hpp"
#endif
