#include "SystemOverlay.hpp"

SystemOverlay* SystemOverlay::_me;

bool SystemOverlay::Init(){
    esp_err_t err = nvs_flash_init();

    if(err != ESP_OK){
        return false;
    }

    tcpip_adapter_init();
    err = esp_event_loop_init(SystemOverlay::event_handler, NULL);

    return err == ESP_OK;
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
    SystemListener* iterator = SystemOverlay::Instance()->_head;
    while(iterator != NULL){
        if(iterator->ApplyFilter(event->event_id)){
            iterator->DataHandler(event);
        }
        iterator = iterator->next;
    }

    return ESP_OK;
}

bool SystemOverlay::RegisterListener( SystemListener* listener){
    if(listener == NULL){
        return false;
    }

    if(_head == NULL){
        _head = listener;
        _tail = listener;
        listener->next = NULL;
        listener->previous = NULL;
    }else{
        _tail->next = listener;
        listener->previous = _tail;
        _tail = listener;
    }

    return true;
}

bool SystemOverlay::UnregisterListener(SystemListener* listener){
    if(listener == NULL){
        return false;
    }

    if(_head != NULL){
        SystemListener* iterator = _head;

        while(iterator != NULL){
            if(iterator->_id == listener->_id){
                if(iterator->previous != NULL){
                    iterator->previous->next = iterator->next;
                }
                if(iterator->next != NULL){
                    iterator->next->previous = iterator->previous;
                }
                return true;
            }
            iterator = iterator->next;
        }
    }

    return false;
}

void SystemOverlay::DelayMillis(int millis){
    vTaskDelay(millis / portTICK_PERIOD_MS);
}

void SystemOverlay::DelayMicros(int micros){
    if(micros) {
        unsigned long endat = Micros();
        endat += micros;
        while(Micros() < endat) {
            asm volatile ("nop");
        }
    }
}

uint32_t SystemOverlay::Micros()
{
    uint32_t ccount;
    __asm__ __volatile__ ( "rsr     %0, ccount" : "=a" (ccount) );
    return ccount / CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ;
}

uint32_t SystemOverlay::Millis()
{
    return Micros()/1000;
}