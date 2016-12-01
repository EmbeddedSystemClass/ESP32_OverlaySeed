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

int app_main(void)
{
    SystemOverlay::Instance()->Init();
    WIFIOverlay::Instance()->Init();

    WIFIOverlay::Instance()->Start();
    WIFIOverlay::Instance()->ScanNetworks(true);

    ESP_LOGW("MAIN","WiFiOverlay scan done");

    while(!WIFIOverlay::Instance()->ScanDone()){
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }

    if(WIFIOverlay::Instance()->NearbyAP() != NULL){
        ESP_LOGW("MAIN","Detected wireless network : %d", WIFIOverlay::Instance()->NearbyAP()->APCount);
    }

    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    int level = 0;
    while (true) {
        gpio_set_level(GPIO_NUM_5, level);
        level = !level;
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }

    return 0;
}