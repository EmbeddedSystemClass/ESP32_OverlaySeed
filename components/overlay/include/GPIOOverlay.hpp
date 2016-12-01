#ifndef _GPIO_OVERLAY_H_
#define _GPIO_OVERLAY_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "esp_system.h"
#include "driver/gpio.h"

#ifdef __cplusplus
}
#endif

class GPIOOverlay{
public:

    bool SetDirection(gpio_num_t pin, gpio_mode_t mode);

    bool DigitalRead(gpio_num_t pin);
    bool DigitalWrite(gpio_num_t pin, bool value);

    uint16_t AnalogRead(gpio_num_t pin);
    uint16_t AnalogWrite(gpio_num_t pin, uint8_t value);

    static GPIOOverlay* Instance();
private:
    GPIOOverlay();

    static GPIOOverlay* _me;
};

#endif