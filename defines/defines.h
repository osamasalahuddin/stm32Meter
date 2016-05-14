/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/* Put your global defines for all libraries here used in your project */
#include "misc.h"
#include "stm32f4xx_conf.h"


/* Change custom SPI for LCD */
/* 
		PB5					MOSI
		PB4         MISO
		PB3         SCK
*/
#define ILI9341_SPI                 SPI3 //OR something similar
#define ILI9341_SPI_PINS            TM_SPI_PinsPack_1
 
/* Change custom CS, DC and RESET pins */
/* CS pin */
#define ILI9341_CS_PORT             GPIOC
#define ILI9341_CS_PIN              GPIO_PIN_2
/* WRX or DC pin */
#define ILI9341_WRX_PORT            GPIOD
#define ILI9341_WRX_PIN             GPIO_PIN_13
/* RST pin */
#define ILI9341_RST_PORT            GPIOD
#define ILI9341_RST_PIN             GPIO_PIN_12

#endif
