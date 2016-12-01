#ifndef __SYSTEM_LISTENER_H
#define __SYSTEM_LISTENER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "esp_system.h"
#include "esp_event.h"

#ifdef __cplusplus
}
#endif

class SystemListener{
public:
    virtual void DataHandler(system_event_t *event) = 0;
    virtual bool ApplyFilter(system_event_id_t event_id) = 0;
    
    SystemListener();

    SystemListener* next;
    SystemListener* previous;

    uint16_t _id;
};

#endif