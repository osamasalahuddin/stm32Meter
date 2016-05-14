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
    //Initialize system
    SystemInit();

		init_Reed();
		init_UART();

/*		USART_puts(USART1, "Hello World\n"); */
	
		//Initialize ILI9341
    TM_ILI9341_Init();
    //Rotate LCD for 90 degrees
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
    //FIll lcd with color
    TM_ILI9341_Fill(ILI9341_COLOR_MAGENTA);

		draw_Meter();
    
    //Put string with black foreground color and red background with 11x18px font
    TM_ILI9341_Puts(245, 225, "idealojy", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

    while (1) {

			int i = 0;
			Toggle_Left_Indicator();
			Toggle_Right_Indicator();
			Toggle_BT_Indicator();
			Toggle_Headlight_Indicator();
			Toggle_Fuel_Indicator(0);
			
			if (update_Reed())
			{

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
				const char token = ' ';
				
				/* Tokenize the first string to extract the RC */
				rc = strtok((char *)received_string, &token);

				/* Type casting rc's value into int to get Request Codes */
				switch((int)rc[0])
				{
					case RC_SMS:
					{
						/* Sms Received Display the Name on the Screen */
						
						rc = strtok((char*)received_string, NULL);
						
						//Put string with black foreground color and red background with 11x18px font
						TM_ILI9341_Puts(140, 225, rc, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);


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


