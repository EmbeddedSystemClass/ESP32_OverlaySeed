#include "SystemOverlay.hpp"

SystemOverlay* SystemOverlay::_me;

bool SystemOverlay::Init(){
    esp_err_t err = nvs_flash_init();

    if(err != ESP_OK){
        return false;
    }

    tcpip_adapter_init();
    err = esp_event_loop_init(SystemOverlay::event_handler, NULL);

    return err != ESP_OK;
}

SystemOverlay* SystemOverlay::Instance(){
    if(SystemOverlay::_me == NULL){
        _me = new SystemOverlay();
    }
    return _me;
}

SystemOverlay::SystemOverlay(){
}

esp_err_t SystemOverlay::event_handler(void *ctx, system_event_t *event){
    return ESP_OK;
}