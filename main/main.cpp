#define GPIO_OVERLAY

#include "Application.hpp"

#define TAG "APP_MAIN"

int app_main(void)
{
    SystemOverlay::Instance()->Init();

	GPIOOverlay::Instance()->InitTouchPad();
    GPIOOverlay::Instance()->SetMode(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    while (true) {
		if (GPIOOverlay::Instance()->ReadTouchPad(TOUCH_PAD_NUM0) < 300) {
			GPIOOverlay::Instance()->DigitalWrite(GPIO_NUM_5, HIGH);
		}
		else {
			GPIOOverlay::Instance()->DigitalWrite(GPIO_NUM_5, LOW);
		}
    }
    return 0;
}