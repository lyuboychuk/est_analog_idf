#include <tracer.h>
#ifdef TRACE_ON
#pragma message "Tracer mode"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

extern const char *TAG;
extern int adc_read_voltage_mv();
extern int adc_read_voltage_rw();

void main_task() {
    int val;
    int raw;
    while (1) {
        val = adc_read_voltage_mv();
        raw = adc_read_voltage_rw();
        ESP_LOGI(TAG, "Voltage: %d mV, raw: %d", val, raw);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
#endif