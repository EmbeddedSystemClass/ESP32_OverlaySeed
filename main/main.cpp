#define GPIO_OVERLAY
#define WIFI_OVERLAY

#include "Application.hpp"

#define TAG "APP_MAIN"

#define WIFI_SSID CONFIG_WIFI_SSID
#define WIFI_PASS CONFIG_WIFI_PASSWORD

int app_main(void)
{
	if (SystemOverlay::Instance()->Init()) {
		ESP_LOGW(TAG, "System initialized");
		WIFIOverlay::Instance()->Init();
		ESP_LOGW(TAG, "WIFI initialized");

		WIFIOverlay::Instance()->ConfigureAP(WIFI_SSID, WIFI_PASS);
		ESP_LOGW(TAG, "Station configured");
		WIFIOverlay::Instance()->Start();
		WIFIOverlay::Instance()->Connect();
		ESP_LOGW(TAG, "Wifi connected");

		GPIOOverlay::Instance()->SetMode(GPIO_NUM_5, GPIO_MODE_OUTPUT);
		while (true) {
			GPIOOverlay::Instance()->DigitalWrite(GPIO_NUM_5, HIGH);
			SystemOverlay::Instance()->DelayMillis(500);
			GPIOOverlay::Instance()->DigitalWrite(GPIO_NUM_5, LOW);
			SystemOverlay::Instance()->DelayMillis(500);
		}
	}
	
    return 0;
}
