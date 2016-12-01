#ifndef _WIFI_HELPER_H
#define _WIFI_HELPER_H

#ifdef __cplusplus
extern "C"{
#endif

#include "string.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"

#ifdef __cplusplus
}
#endif

#include "SystemListener.hpp"

class APList{
public:
    uint8_t APCount;
    wifi_ap_record_t* List;

    ~APList(){free(List);};
};

class WIFIOverlay : public SystemListener{
public:
    esp_err_t Init(wifi_mode_t mode = WIFI_MODE_STA);

    esp_err_t ConfigureSTA(const char* ssid, 
                        const char* password = NULL, 
                        bool hidden = false);

    esp_err_t ConfigureAP(const char* ssid, 
                        const char* password = NULL, 
                        wifi_auth_mode_t auth = WIFI_AUTH_OPEN,
                        bool hidden = false, 
                        int channel = 11);

    virtual void DataHandler(system_event_t *event);
    virtual bool ApplyFilter(system_event_id_t event_id);

    esp_err_t Start();
    esp_err_t Connect();
    
    esp_err_t ScanNetworks(bool block = false);
    APList* NearbyAP();
    bool ScanDone();

    static WIFIOverlay* Instance();

private:
    bool _started;

    APList* _apList;

    WIFIOverlay();
    static WIFIOverlay* _me;
};

#endif