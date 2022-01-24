#include "_uart.h"


#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)


void uart_init(void) {
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_2, 2048, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_2,&uart_config);
    uart_set_pin(UART_NUM_2,TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

}
int sendData(const char* logName, const char* data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_2, data, len);
    //ESP_LOGI(logName, "Wrote %d bytes", txBytes);
    return txBytes;
}

void recvData(char* buffer,size_t count,TickType_t block_time)
{
	const char* RX_TASK_TAG="RX TASK";
	int i=0;
        const int rxBytes = uart_read_bytes(UART_NUM_2, buffer, count,block_time);
        if (rxBytes > 0) {
			buffer[rxBytes+1]='\0';
   //         ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, buffer);
//			sendData(RX_TASK_TAG,(const char*)buffer);
		}
}
