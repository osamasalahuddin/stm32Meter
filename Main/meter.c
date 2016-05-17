#include "meter.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"

char flags_meter;
void draw_Meter()
{
	//Draw white circle
    TM_ILI9341_DrawCircle(METER_X, METER_Y, METER_RADIUS, ILI9341_COLOR_GREEN);
    
	//Draw red filled circle
    TM_ILI9341_DrawFilledCircle(METER_X, METER_Y, METER_RADIUS, ILI9341_COLOR_BLUE2);

	//Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(SPEED_STRING_X, SPEED_STRING_Y, "Speed : ", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
    
	//Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(RPM_STRING_X, RPM_STRING_Y, "RPM   : ", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
    
	//Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(DISTANCE_STRING_X, DISTANCE_STRING_Y, "Dist  : ", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);

}

void update_Meter(int Speed, int Distance, int RPM)
{
	update_Speed(Speed);
	update_Distance(Distance);
	update_RPM(RPM);

}

void update_Speed(int Speed)
{
	char data[100];
	sprintf(data, " %d km/h \r\n", Speed );
	TM_ILI9341_Puts( SPEED_X, SPEED_Y, data, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);

}

void update_Distance(int Speed)
{
	char data[100];
	sprintf(data, " %d km \r\n", Speed );
	TM_ILI9341_Puts( DISTANCE_X, DISTANCE_Y, data, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);

}

void update_RPM(int Speed)
{
	char data[100];
	sprintf(data, " %d rev/s \r\n", Speed );
	TM_ILI9341_Puts( RPM_X, RPM_Y, data, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);

}

void Toggle_Left_Indicator()
{
	static char left_Indicator_flag = 0;
	
	if (left_Indicator_flag == 0)
	{
		//Draw Left Arrow Icon with 16x14px font
    TM_ILI9341_Draw_LeftArrow(5, 0, ILI9341_COLOR_ORANGE, ILI9341_COLOR_MAGENTA);
		left_Indicator_flag = 1;
	}
	else 
	{
		//Remove Left Arrow Icon with 16x14px font
    TM_ILI9341_Draw_LeftArrow(5, 0, ILI9341_COLOR_MAGENTA, ILI9341_COLOR_MAGENTA);
		left_Indicator_flag = 0;
	}
}

void Toggle_Right_Indicator()
{
	static char right_Indicator_flag = 0;
	
	if (right_Indicator_flag == 0)
	{
		//Draw Right Arrow Icon with 16x14px font
    TM_ILI9341_Draw_RightArrow(25, 0, ILI9341_COLOR_ORANGE, ILI9341_COLOR_MAGENTA);
		right_Indicator_flag  = 1;
	}
	else 
	{
		//Remove Right Icon with 16x14px font
    TM_ILI9341_Draw_RightArrow(25, 0, ILI9341_COLOR_MAGENTA, ILI9341_COLOR_MAGENTA);
		right_Indicator_flag  = 0;
	}
}

void Toggle_BT_Indicator()
{
	static char bt_Indicator_flag = 0;
	
	if (bt_Indicator_flag == 0)
	{	
		//Draw Bluetooth Icon with 11x18px font
    TM_ILI9341_Draw_Bluetooth(245, 0, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_MAGENTA);
		bt_Indicator_flag  = 1;
	}
	else 
	{
	
		//Draw Bluetooth Icon with 11x18px font
    TM_ILI9341_Draw_Bluetooth(245, 0, &TM_Font_7x10, ILI9341_COLOR_MAGENTA, ILI9341_COLOR_MAGENTA);
		bt_Indicator_flag  = 0;
	}
}

void Toggle_Headlight_Indicator()
{
	static char headlight_Indicator_flag = 0;
	
	if (headlight_Indicator_flag == 0)
	{	

		//Draw Headlight Icon with 16x14px font
    TM_ILI9341_Draw_Headlight(50, 0, ILI9341_COLOR_ORANGE, ILI9341_COLOR_MAGENTA);
		headlight_Indicator_flag = 1;
	}
	else 
	{

		//Draw Headlight Icon with 16x14px font
    TM_ILI9341_Draw_Headlight(50, 0, ILI9341_COLOR_MAGENTA, ILI9341_COLOR_MAGENTA);
		headlight_Indicator_flag = 0;
	}
}

void Toggle_Fuel_Indicator(short percentage)
{
	static char fuel_Indicator_flag = 0;
	
	if (fuel_Indicator_flag == 0)
	{	

		//Draw Fuel Icon with 16x14px font
    TM_ILI9341_Draw_Fuel(70, 0, percentage/10, ILI9341_COLOR_ORANGE, ILI9341_COLOR_MAGENTA);
		fuel_Indicator_flag  = 1;
	}
	else 
	{
	
		//Draw Fuel Icon with 16x14px font
    TM_ILI9341_Draw_Fuel(70, 0, percentage, ILI9341_COLOR_MAGENTA, ILI9341_COLOR_MAGENTA);
		fuel_Indicator_flag  = 0;
	}
}

int parseString(char* str, char* name, char* number)
{
	int code;
	char *rc;
	const char token = ';';

	/* Tokenize the first string to extract the RC string */
	rc = strtok((char *)str, &token);

	/* Parse the string and extract RCs and other information */
	code = Ascii2Hex(rc);

	/* Tokenize the first string to extract the Contact Number */
	name = strtok((char *)str, NULL);

	/* Tokenize the first string to extract the Contact Name */
	number = strtok((char *)str, NULL);

	return code;
}

void draw_CallerName(char* str, char* name, char* number)
{
	/* Draw the calling persons Name on the meter */
	
	int code;
	char *rc;
	const char token = ';';

	/* Parse the string and extract RCs and other information */

	/* Tokenize the first string to extract the RC */
	rc = strtok((char *)str, &token);
	
	code = (int) Ascii2Hex(rc);
	
	//Put string with black foreground color and red background with 11x18px font
	TM_ILI9341_Puts(210, 125, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

	/* Tokenize the first string to extract the RC */
	rc = strtok((char *)str, NULL);

	//Put string with black foreground color and red background with 11x18px font
	TM_ILI9341_Puts(210, 145, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

}

int draw_SMSName(char* str)
{
	/* Draw the calling persons Name on the meter */
	
	int code;
	char *rc;
	const char token = ';';

	/* Parse the string and extract RCs and other information */

	/* Tokenize the first string to extract the RC */
	rc = strtok((char *)str, &token);
	
	code = (int) Ascii2Hex(rc);
	
	//Put string with black foreground color and red background with 11x18px font
	TM_ILI9341_Puts(210, 75, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

	/* Tokenize the first string to extract the RC */
	rc = strtok((char *)str, NULL);

	//Put string with black foreground color and red background with 11x18px font
	TM_ILI9341_Puts(210, 95, str, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

}

int Ascii2Hex(char *arr)
{
	/* Converts the 2 digit ASCII numbers to their hex values */
	int num = (arr[0]-0x30) * 10 + arr[1]-0x30;

	return num;
}
