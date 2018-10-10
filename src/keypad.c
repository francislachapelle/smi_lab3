/*
 * keypad.c
 *
 *  Created on: Oct 9, 2018
 *      Author: franc
 */

#include "keypad.h"

/* Private variables */
uint8_t KEYPAD_INT_Buttons[4][4] =
{
	{0x01, 0x02, 0x03},
	{0x04, 0x05, 0x06},
	{0x07, 0x08, 0x09},
	{0x0A, 0x00, 0x0B},
};

/* Public function definitions */


void init_keypad(void)
{


}

void keypad_update(void);
