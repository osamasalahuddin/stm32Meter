/**
 *    Keil project for ILI9341 LCD example
 *
 */
 
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include "stm32f4xx_usart.h"
#include <stdio.h>
#include "init.h"
#include "meter.h"
 
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;
int SpeedCounter = 0;
int DistanceCounter = 0;
int RPMCounter = 0;


int main(void) {
    
		init_Reed();
		init_UART();

		USART_puts(USART1, "Hello World\n");
	
		//Initialize ILI9341
    TM_ILI9341_Init();
    //Rotate LCD for 90 degrees
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
    //FIll lcd with color
    TM_ILI9341_Fill(ILI9341_COLOR_MAGENTA);

		draw_Meter();
    
    //Put string with black foreground color and red background with 11x18px font
    TM_ILI9341_Puts(245, 225, "idealojy", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

    while (1)
		{

			int i = 0;
			Toggle_Left_Indicator();
			Toggle_Right_Indicator();
			Toggle_Headlight_Indicator();
			Toggle_Fuel_Indicator(0);

			if (flags_meter & REED_RECEIVED)
			{

				/* Clear the REED_RECEIVED flag */
				flags_meter &= ~REED_RECEIVED;

				/* Reed switch is short */
				SpeedCounter++;
				update_Speed(SpeedCounter);
				update_Distance(SpeedCounter);
				update_RPM(SpeedCounter);

			}

			if (flags_meter & UART_RECEIVED)
			{

				/* Data received from Bluetooth */
				char *rc;
				volatile char *name;
				volatile char *number;
				char smsBody[200];
				int code;

				/* Clear the UART_RECEIVED flag */
				flags_meter &= ~UART_RECEIVED;

				code = parseString(received_string, name, number);

				/* Type casting rc's value into int to get Request Codes */
				switch(code)
				{
					case RC_SMS:
					{
						/* Sms Received Display the Name on the Screen */
						draw_SMSName((char *)received_string);

						break;
					}
					case RC_CALL:
					{

						/* Call Received Display the Name and number on the Screen */
						draw_CallerName((char *)received_string, name, number);

						break;

					}
					case RC_BLUETOOTH:
					{
						/* Connection Established display the Bluetooth icon */
						Toggle_BT_Indicator();

						break;
					}
					
					default:
						/* Should Never arrive here, If it does then 
							 the app and meter are not in same version */
						break;
				}
			}
			
			while (i++ < 1000000);
    }
}


