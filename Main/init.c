#include "init.h"
#include "meter.h"

volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string

void init_UART()
{
	GPIO_InitTypeDef GPIO_InitStruct; 							// this is for the GPIO pins used as TX and RX
	USART_InitTypeDef USART_InitStructure; 					// this is for the USART1 initialization
	NVIC_InitTypeDef NVIC_InitStructure; 						// this is used to configure the NVIC (nested vector interrupt controller)
	USART_ClockInitTypeDef USART_ClockInitStruct;		// this is for USART1 Clock Initializations
    
	/* enable APB2 peripheral clock for USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* enable the peripheral clock for the pins used by
	 * USART1, PB6 for TX and PB7 for RX
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* This sequence sets up the TX and RX pins
	 * so they work correctly with the USART1 peripheral
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6; 					// Pin 6 (TX) is used
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 			// the pins are configured as alternate function so the USART peripheral has access to them
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	// this defines the IO speed and has nothing to do with the baudrate!
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			// this defines the output type as push pull mode (as opposed to open drain)
	GPIO_Init(GPIOB, &GPIO_InitStruct);							// now all the values are passed to the GPIO_Init() function which sets the GPIO registers
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7; 					// Pin 7 (RX) is used
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;				// this activates the pullup resistors on the IO pins
	GPIO_Init(GPIOB, &GPIO_InitStruct);							// now all the values are passed to the GPIO_Init() function which sets the GPIO registers

	/* The RX and TX pins are now connected to their AF
	 * so that the USART1 can take over control of the
	 * pins
	 */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	/* Make sure syncro clock is turned off */
	USART_ClockStructInit( &USART_ClockInitStruct );
	USART_ClockInit( USART1, &USART_ClockInitStruct  );

	/* USARTx configured as follow:
	 * BaudRate = 115200 baud  
	 * Word Length = 8 Bits
	 * One Stop Bit
	 * No parity
	 * Hardware flow control disabled (RTS and CTS signals)
	 * Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);


	/* Here the USART1 receive interrupt is enabled
	 * and the interrupt controller is configured
	 * to jump to the USART1_IRQHandler() function
	 * if the USART1 receive interrupt occurs
	 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 						// enable the USART1 receive interrupt

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;					// we want to configure the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	// this sets the priority group of the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				// this sets the sub priority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						// the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);														// the properties are passed to the NVIC_Init function which takes care of the low level stuff

	// finally this enables the complete USART1 peripheral
	USART_Cmd(USART1, ENABLE);
}

void init_Reed()
{
	GPIO_InitTypeDef GPIO_InitStructure; 					// this is for the GPIO pins used as TX and RX
	EXTI_InitTypeDef EXTI_InitStructure;					// EXTI Interrupt Configurations
	NVIC_InitTypeDef NVIC_InitStructure; 					// this is used to configure the NVIC (nested vector interrupt controller)
	
	/* Configure AHB1 Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* GPIO configured as follows:
	 * GPIO Pin = PE5
	 * GPIO Mode = Input
	 * GPIO PullUp = Pull Down
	 * GPIO Speed = Medium Speed
	 */
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;

	GPIO_Init(GPIOE,&GPIO_InitStructure);

  /* Connect EXTI Line0 to PE5 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE       , EXTI_PinSource0);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

char update_Reed()
{
	/* Set REED_RECEIVED flag */
	/* flags_meter |= REED_RECEIVED; */
	return	(char)(GPIO_ReadInputData(GPIOE) & GPIO_Pin_5);
}


// this is the interrupt request handler (IRQ) for ALL USART1 interrupts
void USART1_IRQHandler(void)
{

	// check if the USART1 receive interrupt flag was set
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		static uint8_t cnt = 0; // this counter is used to determine the string length
		char t = USART1->DR; // the character from the USART1 data register is saved in t

		/* Set UART_RECEIVED flag */
		flags_meter |= UART_RECEIVED;

		/* check if the received character is not the LF character (used to determine end of string)
		 * or the if the maximum string length has been been reached
		 */
		if( (t != '\n') && (cnt < MAX_STRLEN) ){
			received_string[cnt] = t;
			cnt++;
			
		}
		else{ // otherwise reset the character counter and print the received string
			cnt = 0;
			/*USART_puts(USART1, received_string);*/
		}
	}
}

/* This function handles External line 0 interrupt request. */
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Set REED_RECEIVED flag */
		flags_meter |= REED_RECEIVED;

    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/* This function is used to transmit a string of characters via
 * the USART specified in USARTx.
 *
 * It takes two arguments: USARTx --> can be any of the USARTs e.g. USART1, USART2 etc.
 * 						   (volatile) char *s is the string you want to send
 *
 * Note: The string has to be passed to the function as a pointer because
 * 		 the compiler doesn't know the 'string' data type. In standard
 * 		 C a string is just an array of characters
 *
 * Note 2: At the moment it takes a volatile char because the received_string variable
 * 		   declared as volatile char --> otherwise the compiler will spit out warnings
 * */
void USART_puts(USART_TypeDef* USARTx, volatile char *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *s);
		*s++;
	}
}

