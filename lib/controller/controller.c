#include "controller.h"
#ifndef TRACE_ON
#pragma message "Motor or led controller"

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

extern int adc_read_voltage_mv(int *raw);

static const uint32_t max_= 3152;
static const uint32_t res = 100;
static const uint32_t ub = 0;
static const uint32_t lb = 100;

void main_task() {
    
    gpio_config_t cntl_conf = {
        .pin_bit_mask = 1ULL << CNTL_PIN,
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE
    };
    
    gpio_config(&cntl_conf);
    gpio_set_level(CNTL_PIN, 0);

    uint32_t pwm = 0;
    int raw; 
    while (1) {        
        pwm = (adc_read_voltage_mv(&raw) * res) / max_;
        if (pwm > ub) {
            gpio_set_level(CNTL_PIN, 1);     
            esp_rom_delay_us(pwm);            
        }
        if (pwm < lb) {
            gpio_set_level(CNTL_PIN, 0); 
            esp_rom_delay_us(res - pwm);
        } 
    }
}

#endif