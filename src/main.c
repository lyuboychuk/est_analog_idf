#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

#define M_TRACE_ON
#include <bundle.h>

#define LED_PIN1 7
#define ADC_CHAN ADC_CHANNEL_8 
#define ATTENUATION ADC_ATTEN_DB_12
#define RESOLUTION ADC_BITWIDTH_12

const char *TAG = "ADC Trace: ";
static adc_oneshot_unit_handle_t adc_handle;
static adc_cali_handle_t cali_handle;
bool cali_enabled = false;

void setup(void)
{
    gpio_config_t led_conf = {
        .pin_bit_mask = 1ULL << LED_PIN1,
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE
    };
    gpio_config(&led_conf);
    gpio_set_level(LED_PIN1, 1);

    // ADC unit
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1,                  
    };
    // ADC channel
    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = RESOLUTION,
        .atten = ATTENUATION, 
    };
    adc_cali_curve_fitting_config_t cali_cfg = {
        .unit_id = ADC_UNIT_1,
        .chan = ADC_CHAN,
        .atten = ATTENUATION,
        .bitwidth = RESOLUTION,
    };
    
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&unit_cfg, &adc_handle));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHAN, &chan_cfg));

    if (adc_cali_create_scheme_curve_fitting(&cali_cfg, &cali_handle) == ESP_OK) {
        cali_enabled = true;
        ESP_LOGI("ADC", "ADC calibration enabled (real Vref from eFuse)");
    } else {
        ESP_LOGW("ADC", "ADC calibration NOT available");
    }
    ESP_LOGI(TAG, "ACD initialized");
}
int adc_read_voltage_rw(void) {
    int raw = 0; 
    ESP_ERROR_CHECK(
        adc_oneshot_read(adc_handle, ADC_CHAN, &raw)
    );
    return raw;
}
int adc_read_voltage_from_raw(int raw)
{
    int voltage_mv = 0;

    if (cali_enabled) {
        ESP_ERROR_CHECK(
            adc_cali_raw_to_voltage(cali_handle, raw, &voltage_mv)
        );
        return voltage_mv; 
    }

    return -1; 
}
int adc_read_voltage_mv(void)
{
    int raw = adc_read_voltage_rw();    
    int voltage_mv = 0;

    if (cali_enabled) {
        ESP_ERROR_CHECK(
            adc_cali_raw_to_voltage(cali_handle, raw, &voltage_mv)
        );
        return voltage_mv; 
    }

    return -1; 
}

void app_main(void)
{
    setup();
    main_task();
}