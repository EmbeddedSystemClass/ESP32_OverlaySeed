#include "GPIOOverlay.hpp"

GPIOOverlay* GPIOOverlay::_me;

bool GPIOOverlay::SetDirection(gpio_num_t pin, gpio_mode_t mode){
    return gpio_set_direction(pin, mode) == ESP_OK;
}

bool GPIOOverlay::DigitalRead(gpio_num_t pin){
    return gpio_get_level(pin) > 0;
}

bool GPIOOverlay::DigitalWrite(gpio_num_t pin, bool value){
    if(value){
        return gpio_set_level(pin, 1) == ESP_OK;
    }else{
        return gpio_set_level(pin, 0) == ESP_OK;
    }
}

uint16_t GPIOOverlay::AnalogRead(gpio_num_t pin){
    return 0;
}

uint16_t GPIOOverlay::AnalogWrite(gpio_num_t pin, uint8_t value){
    return 0;
}

GPIOOverlay* GPIOOverlay::Instance(){
    if(_me == NULL){
        _me = new GPIOOverlay();
    }

    return _me;
}

GPIOOverlay::GPIOOverlay(){

}