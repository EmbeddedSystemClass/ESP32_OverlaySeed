#ifdef __cplusplus
extern "C"{
#endif

#include "esp_system.h"
#include "driver/gpio.h"

int app_main(void);

#ifdef __cplusplus
}
#endif

#include "SystemOverlay.hpp"

int app_main(void)
{

    if(!SystemOverlay::Instance()->Init()){
        printf("Error in Overlay init");
    }
    
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    int level = 0;
    while (true) {
        gpio_set_level(GPIO_NUM_4, level);
        level = !level;
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }

    return 0;
}