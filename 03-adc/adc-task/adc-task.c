#include "hardware/adc.h"

#include "pico/stdlib.h"
#include "stdio.h"
#include "stdlib.h"
#include "hardware/gpio.h"

static adc_task_state_t adc_state = IDLE;
uint64_t time;
uint ADC_TASK_MEAS_PERIOD_US = 100000;
const int adc_pin = 26;
const int adc_ch = 0;
const int adc_temp_ch = 4;
float voltage;
float temp_C;

void adc_task_init(){
    adc_init();
    adc_gpio_init(adc_pin);
    adc_set_temp_sensor_enabled(true);
}

float adc_task_getV(){
    adc_select_input(adc_ch);
    uint16_t voltage_counts = adc_read();
    voltage=3.3/4096*voltage_counts;
    return voltage;
}

float adc_task_getT(){
    adc_select_input(adc_temp_ch);
    uint16_t voltage_counts = adc_read();
    voltage=3.3/4096*voltage_counts;
    temp_C = 27.0f - (voltage - 0.706f) / 0.001721f;
}