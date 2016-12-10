#include "GPIOOverlay.hpp"

GPIOOverlay* GPIOOverlay::_me;

bool GPIOOverlay::SetMode(gpio_num_t pin, gpio_mode_t mode){
    return gpio_set_direction(pin, mode) == ESP_OK;
}

bool GPIOOverlay::DigitalRead(gpio_num_t pin){
    return gpio_get_level(pin) > 0;
}

bool GPIOOverlay::DigitalWrite(gpio_num_t pin, bool value){
    if(value){
        return gpio_set_level(pin, HIGH) == ESP_OK;
    }else{
        return gpio_set_level(pin, LOW) == ESP_OK;
    }
}

uint16_t GPIOOverlay::AnalogRead(adc1_channel_t pin, adc_atten_t atten)
{
	adc1_config_channel_atten(pin, atten);
	return adc1_get_voltage(pin);
}

bool GPIOOverlay::SetAnalogWidth(adc_bits_width_t bits)
{
	return adc1_config_width(bits) == ESP_OK;
}

bool GPIOOverlay::SetAnalogAttenuation(adc1_channel_t channel, adc_atten_t atten)
{
	return adc1_config_channel_atten(channel,atten) == ESP_OK;
}

int GPIOOverlay::HallRead()
{
	adc1_config_width(ADC_WIDTH_12Bit);
	return hall_sensor_read();
}

bool GPIOOverlay::DACWrite(dac_channel_t channel, uint8_t dac_value)
{
	return dac_out_voltage(channel,dac_value) == ESP_OK;
}

void GPIOOverlay::InitTouchPad()
{
	if (_touchpadInitialized) {
		return;
	}

	touch_pad_init();
	_touchpadInitialized = true;
}

bool GPIOOverlay::ConfigTouchPad(touch_pad_t touch_num, uint16_t threshold)
{
	return touch_pad_config(touch_num,threshold) == ESP_OK;
}

uint16_t GPIOOverlay::ReadTouchPad(touch_pad_t touch_num)
{
	uint16_t ret = -1;
	if (touch_pad_read(touch_num, &ret) == ESP_OK) {
		return ret;
	}

	return -1;
}

bool GPIOOverlay::RegisterTouchPadInterrupt(uint32_t touch_intr_num, isr_handler handler, void * arg)
{
	return touch_pad_isr_handler_register(touch_intr_num,handler,arg) == ESP_OK;
}

GPIOOverlay* GPIOOverlay::Instance(){
    if(_me == NULL){
        _me = new GPIOOverlay();
    }

    return _me;
}

GPIOOverlay::GPIOOverlay(){
	SetAnalogWidth(ADC_WIDTH_12Bit);
}