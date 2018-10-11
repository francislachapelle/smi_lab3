/**
 * Modified by Francis Lachapelle for SMI.
 * */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"

#define 	CMD_LCD_CLEAR						0x01
#define		CMD_LCD_HOME						0x02
#define 	CMD_LCD_FUNCTION_2_LINES_8_BITS		0x38
#define		CMD_LCD_DISPLAY_ON					0x0E
#define		CMD_LCD_CHANGE_LINE					0xC0

void initLcd(void);
void writeCommand(unsigned short p_command);
void writeSymbol(char * p_symbol, uint8_t size_of_symbol);
void updateLcd(void);

#endif //__LCD_H
