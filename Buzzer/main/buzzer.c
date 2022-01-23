#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>

#define ALARM_PIN 15

void SensorTask(void* parameters)
{
    for ( ;;)
    {
        printf("sensor task\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}

void BuzzerTask(void* parameters)
{   

    //gpio_config();
    
    gpio_reset_pin(ALARM_PIN);
    gpio_set_direction(ALARM_PIN,GPIO_MODE_OUTPUT);
    for(;;)
    {
        printf("Toggling buzzer\n");
        gpio_set_level(ALARM_PIN,0);
        vTaskDelay(500/portTICK_PERIOD_MS);
        gpio_set_level(ALARM_PIN,1);
        vTaskDelay(400/portTICK_PERIOD_MS);
        printf("Toggling done\n");
    }
    vTaskDelete(NULL);
}


void app_main()
{
    BaseType_t result;
    result=xTaskCreate(SensorTask,"Sensor Task",2048,NULL,2,NULL);
    if(result == pdPASS)
    {
        printf("task1 is created\n");
    }
    printf("creating task2\n");

    result=xTaskCreate(BuzzerTask,"Buzzer Task",2048,NULL,2,NULL); 
    if(result == pdPASS)
    {
        printf("task2 is created\n");
    }


}