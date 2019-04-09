/* 
 * File:   uart_sw.h
 * Author: james
 *
 * Created on 9 April 2019, 11:55 AM
 */

#ifndef UART_SW_H
#define	UART_SW_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
#define UART_SW_TX_PIN  UART_SW
    
    typedef struct{
        uint8_t data;
        uint8_t isEmpty;
    }uart_sw_data_t;
    
    /* setup the stuff for software uart */
    void UartSW_init(void);
    
    /* a task to run in timer interrupt to clock out uart data */
    void UartSW_task(void);
    
    /* send one byte */
    void UartSW_putc(uint8_t);
    
    /* get buffer state */
    uint8_t UartWS_isEmpty(void);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_SW_H */

