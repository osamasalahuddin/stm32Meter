#ifndef __INIT_H__
#define __INIT_H__

#include "stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define		MAX_STRLEN			50U

char update_Reed(void);
void init_Reed(void);
void init_UART(void);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);

extern volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string


#endif
