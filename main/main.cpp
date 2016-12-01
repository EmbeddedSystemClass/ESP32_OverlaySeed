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
#include "WIFIOverlay.hpp"
#include "GPIOOverlay.hpp"

int app_main(void)
{
    SystemOverlay::Instance()->Init();
    WIFIOverlay::Instance()->Init();

    WIFIOverlay::Instance()->Start();
    WIFIOverlay::Instance()->ScanNetworks(true);

    while(!WIFIOverlay::Instance()->ScanDone()){
        SystemOverlay::Instance()->DelayMillis(300);
    }

    GPIOOverlay::Instance()->SetDirection(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    bool level = true;
    while (true) {
        GPIOOverlay::Instance()->DigitalWrite(GPIO_NUM_5, level);
        level = !level;
        SystemOverlay::Instance()->DelayMillis(500);
    }

    return 0;
}