#include "WIFIOverlay.hpp"
#include "SystemOverlay.hpp"

WIFIOverlay* WIFIOverlay::_me;

bool WIFIOverlay::Init(wifi_mode_t mode){
    _started = false;
    esp_err_t err = ESP_OK;
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    err = esp_wifi_init(&cfg);
    err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    err = esp_wifi_set_mode(mode);
    
    SystemOverlay::Instance()->RegisterListener(this);

    return err == ESP_OK;
}

bool WIFIOverlay::ConfigureSTA(const char* ssid, const char* password, bool hidden){
    esp_err_t err = ESP_OK;

    wifi_config_t* wifi_config = (wifi_config_t*)malloc(sizeof(wifi_config_t));
    err = esp_wifi_get_config(WIFI_IF_AP,wifi_config);
    strcpy(wifi_config->sta.ssid,ssid);
    if(password != NULL){
        strcpy(wifi_config->sta.password,password);
    }

    wifi_config->sta.bssid_set = !hidden;

    err = esp_wifi_set_config(WIFI_IF_STA, wifi_config);
    free(wifi_config);

    return err == ESP_OK;
}

bool WIFIOverlay::ConfigureAP(const char* ssid, 
                                            const char* password, 
                                            wifi_auth_mode_t auth,
                                            bool hidden, 
                                            int channel){
    esp_err_t err = ESP_OK;
    wifi_config_t* wifi_config = (wifi_config_t*)malloc(sizeof(wifi_config_t));
    err = esp_wifi_get_config(WIFI_IF_AP,wifi_config);
    
    strcpy(wifi_config->ap.ssid,ssid);
    if(password != NULL){
        strcpy(wifi_config->ap.password,password);
    }

    wifi_config->ap.ssid_len = strlen(wifi_config->ap.ssid);
    wifi_config->ap.channel = channel;
    wifi_config->ap.authmode = auth;
    wifi_config->ap.ssid_hidden =hidden;
    wifi_config->ap.max_connection = 4;
    wifi_config->ap.beacon_interval = 100;
    
    err = esp_wifi_set_config(WIFI_IF_AP,wifi_config);
    free(wifi_config);
    return err == ESP_OK;
}

bool WIFIOverlay::Start(){
    esp_err_t err = ESP_OK;
    if(!_started){
        err = esp_wifi_start();
    }    
    if(err == ESP_OK){
        _started = true;
    }
    return err == ESP_OK;
}

bool WIFIOverlay::Connect(){
    return esp_wifi_connect() == ESP_OK;
}

bool WIFIOverlay::ScanNetworks(bool block){
    esp_err_t err = ESP_OK;

    wifi_scan_config_t scanConf = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true
    };

    if(_apList != NULL){
        delete _apList;
        _apList = NULL;
    }

    err = esp_wifi_scan_start(&scanConf, block);

    return err == ESP_OK;
}

void WIFIOverlay::DataHandler(system_event_t *event){
    if(SYSTEM_EVENT_SCAN_DONE == event->event_id){
        uint16_t apCount = 0;
        esp_wifi_scan_get_ap_num(&apCount);
        wifi_ap_record_t *list = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * apCount);
        esp_wifi_scan_get_ap_records(&apCount, list);
        if(_apList != NULL){
            delete _apList;
        }
        _apList = new APList();
        _apList->List = list;
        _apList->APCount = apCount;
    }
}

bool WIFIOverlay::ApplyFilter(system_event_id_t event_id){
    return event_id == SYSTEM_EVENT_SCAN_DONE;
}

WIFIOverlay::WIFIOverlay(){}

WIFIOverlay* WIFIOverlay::Instance(){
    if(_me == NULL){
        _me = new WIFIOverlay();
    }

    return _me;
}

APList* WIFIOverlay::NearbyAP(){
    return _apList;
}

bool WIFIOverlay::ScanDone(){
    return _apList != NULL;
}