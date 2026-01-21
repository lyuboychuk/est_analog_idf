#include <tracer.h>
#ifdef TRACE_ON
#pragma message "Tracer mode"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

extern const char *TAG;
extern int adc_read_voltage_rw();
extern int adc_read_voltage_from_raw(int raw);

void main_task() {
    int max_voltage = 3100;//3152;
    int  max_value = (1<<12)-1; // 12 bit resolution
    
    int N=20;
    int cal_voltage=0,raw_value=0,raw_voltage=0;
    float err_voltage;

    int Avg_raw_value,Avg_cal_voltage, Avg_raw_voltage;
    float Avg_err_voltage = 0.0f;
    

    while (1) { 
        Avg_raw_value = 0;
        Avg_cal_voltage = 0;
        Avg_raw_voltage = 0;
        Avg_err_voltage = 0.0f;
        for (int i=0; i<N; i++) {
            raw_value = adc_read_voltage_rw();    
            cal_voltage = adc_read_voltage_from_raw(raw_value);            
            raw_voltage = (raw_value * max_voltage) / max_value;
            err_voltage = 100.0f*(raw_voltage-cal_voltage)/max_voltage;            

            Avg_raw_value += raw_value;
            Avg_cal_voltage += cal_voltage;
            Avg_raw_voltage += raw_voltage;
            Avg_err_voltage += err_voltage;
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        Avg_raw_value /= N;
        Avg_cal_voltage /= N;
        Avg_raw_voltage /= N;
        Avg_err_voltage /= N;
        ESP_LOGI(
            TAG, 
            "Raw Value: %d, Callibrated Voltage: %d mV, Raw Voltage: %d mV, Error: %.1f%%", 
            Avg_raw_value, Avg_cal_voltage, Avg_raw_voltage, Avg_err_voltage);
    }
}
#endif