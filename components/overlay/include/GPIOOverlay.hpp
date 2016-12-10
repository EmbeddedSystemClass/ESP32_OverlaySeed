#ifndef _GPIO_OVERLAY_H_
#define _GPIO_OVERLAY_H_

#ifdef __cplusplus
extern "C"{
#endif

	#define LOW               0x0
	#define HIGH              0x1

	#include "driver/gpio.h"
	#include "driver/adc.h"
	#include "driver/dac.h"
	#include "driver/touch_pad.h"

	typedef void(*isr_handler)(void*);

#ifdef __cplusplus
}
#endif

class GPIOOverlay{
public:

    bool SetMode(gpio_num_t pin, gpio_mode_t mode);

	/*
		Read the digital input
	*/
    bool DigitalRead(gpio_num_t pin);

	/*
		Write on the digital input
	*/
    bool DigitalWrite(gpio_num_t pin, bool value);

	/*
		Read the analog input
	*/
	uint16_t AnalogRead(adc1_channel_t  pin, adc_atten_t atten = ADC_ATTEN_0db);

	/*
		Set the number of sampling bits (9 - 12)
	*/
	bool  SetAnalogWidth(adc_bits_width_t bits);

	/*
		Set the ADC1 attenuation for the channel
	*/
	bool SetAnalogAttenuation(adc1_channel_t channel, adc_atten_t atten);

	/*
		Get value for HALL sensor (without LNA)
		connected to pins 36(SVP) and 39(SVN)
	*/
	int  HallRead();

	/*
		Write the value on one of the DAC
	*/
    bool DACWrite(dac_channel_t channel, uint8_t dac_value);

	/*
		Enable touch module
	*/
	void InitTouchPad();
	
	/*
		Configure touch pad threshold for the interrupt
	*/
	bool ConfigTouchPad(touch_pad_t touch_num, uint16_t threshold);

	/*
		Read a specific touch pad
	*/
	uint16_t ReadTouchPad(touch_pad_t touch_num);

	/*
		Register touch pad interrupt holder. 
		WARNING : use only INUM that is not used by the system

		The arg parameter will be pass at the handler
	*/
	bool RegisterTouchPadInterrupt(uint32_t touch_intr_num, isr_handler handler, void *arg);

    static GPIOOverlay* Instance();
private:
    GPIOOverlay();

	bool _touchpadInitialized = false;

    static GPIOOverlay* _me;
};

#endif