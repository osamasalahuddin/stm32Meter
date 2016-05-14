#ifndef     __METER_H__
#define     __METER_H__
#include <stdio.h>


void draw_Meter(void);
void update_Meter(int Speed, int Distance, int RPM);
void update_Speed(int Speed);
void update_Distance(int Distance);
void update_RPM(int RPM);
void Toggle_Left_Indicator(void);
void Toggle_Right_Indicator(void);
void Toggle_BT_Indicator(void);
void Toggle_Headlight_Indicator(void);
void Toggle_Fuel_Indicator(short percentage);


/* Meter UI defines */
#define   METER_X               120u
#define   METER_Y               120u
#define   METER_RADIUS          80u
#define   SPEED_STRING_X        60u
#define   SPEED_STRING_Y        90u
#define   DISTANCE_STRING_X     60u
#define   DISTANCE_STRING_Y     110u
#define   RPM_STRING_X          60u
#define   RPM_STRING_Y          130u
#define   SPEED_X               SPEED_STRING_X+75U
#define   SPEED_Y               SPEED_STRING_Y
#define   DISTANCE_X            DISTANCE_STRING_X+75U
#define   DISTANCE_Y            DISTANCE_STRING_Y
#define   RPM_X                 RPM_STRING_X+75U
#define		RPM_Y									RPM_STRING_Y

/* Meter Request Codes */
#define 	RC_SMS								01U
#define		RC_CALL								02U
#define		RC_SPEED							03U
#define		RC_DISTANCE						04U
#define		RC_RPM								05U
#define		RC_BLUETOOTH					06U
#define		RC_FUEL								07U
#define		RC_ENGNE_OIL					08U

/* Interrupt flags for different interrupts */
#define 	UART_RECEIVED					(1u << 0)
#define 	REED_RECEIVED					(1u << 1)
#define 	HEADLIGHT_RECEIVED		(1u << 2)
#define 	LEFT_IND_RECEIVED			(1u << 3)
#define 	RIGHT_IND_RECEIVED		(1u << 4)
#define 	FUEL_RECEIVED					(1u << 5)

extern char flags_meter;
#endif
