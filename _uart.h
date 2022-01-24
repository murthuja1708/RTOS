
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

void uart_init(void); 
int sendData(const char* logName, const char* data);
void recvData(char* ,size_t ,TickType_t);
