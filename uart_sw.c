#include "uart_sw.h"
#include "board.h"
#include "hal.h"
#include "helper.h"

volatile static uart_sw_data_t uart_buf;

void UartSW_init(void) {
    uart_buf.data = 0U;
    uart_buf.isEmpty = 1U;

    UART_SW_TX_PIN = UART_SW_PIN_HIGH;
    delay_ms(1U);   // this need to longer than one bit time for the data rate
}

inline void UartSW_task(void) {
    static uint8_t sm = 0U;

    /* don't do anything is nothing in the buffer */
    if (uart_buf.isEmpty) return;

    /* clock out data */
    switch (sm) {
        case 0: // start bit
            UART_SW_TX_PIN = UART_SW_PIN_LOW;
            break;
        case 1: // bit 1
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8: // bit 8
            UART_SW_TX_PIN = uart_buf.data & 0x01U;
            uart_buf.data = (uint8_t)(uart_buf.data >> 1U);
            break;
        case 9: // stop bit
            UART_SW_TX_PIN = UART_SW_PIN_HIGH;
            break;
    }

    /* done */
    sm++;
    if (sm > 9){
        sm = 0;
        uart_buf.isEmpty = 1U;
    }
}

void UartSW_putc(uint8_t data){
    uart_buf.data = data;
    uart_buf.isEmpty = 0;
}

uint8_t UartSW_isReady(void){
    return (uint8_t)uart_buf.isEmpty;
}