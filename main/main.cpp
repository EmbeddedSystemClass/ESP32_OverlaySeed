#define WIFI_OVERLAY
#define GPIO_OVERLAY

#include "Application.hpp"


int app_main(void)
{
    SystemOverlay::Instance()->Init();

    WIFIOverlay::Instance()->Init();
    WIFIOverlay::Instance()->ConfigureAP("TEST_ESP");
    WIFIOverlay::Instance()->Start();

    GPIOOverlay::Instance()->SetDirection(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    bool level = true;
    while (true) {
        GPIOOverlay::Instance()->DigitalWrite(GPIO_NUM_5, level);
        level = !level;
        SystemOverlay::Instance()->DelayMillis(1000);
    }
    return 0;
}