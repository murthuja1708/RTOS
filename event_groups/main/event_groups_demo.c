#include<stdio.h>
#include<stdlib.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/event_groups.h>



TaskHandle_t temperature_handle;
TaskHandle_t pressure_handle;
TaskHandle_t calibration_handle;

EventGroupHandle_t sensor_eg;

const uint32_t temp_event_bit = (1 << 0);
const uint32_t pressure_event_bit = (1 << 1);
const uint32_t all_bits = (temp_event_bit | pressure_event_bit);

void TemperatureTask(void* args)
{
	for(;;)
	{
		printf("Temperature Task\n");
		xEventGroupSetBits(sensor_eg,temp_event_bit);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


void PressureTask(void* parameters)
{
	for(;;)
	{
		printf("Pressure Task\n");
		xEventGroupSetBits(sensor_eg,pressure_event_bit);
		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}


void CalibrationTask(void* parameters)
{
	uint32_t result;
	for(;;)
	{
		printf("calibration task\n");
		result = xEventGroupWaitBits(sensor_eg,all_bits,pdTRUE,pdTRUE,pdMS_TO_TICKS(1500));
		printf("Result: %d\n",result);
	}
}


void app_main()
{
	
	sensor_eg = xEventGroupCreate();
	xTaskCreate(CalibrationTask,"Calibration Task",2048,NULL,3,&calibration_handle); 

	xTaskCreate(TemperatureTask,"Temperature Task",2048,NULL,4,&temperature_handle);

	xTaskCreate(PressureTask,"Pressure Task",2048,NULL,5,&pressure_handle);

	while(1);
}
