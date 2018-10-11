/**
 * Modified by Francis Lachapelle for SMI.
 * https://github.com/kz3eXodd/lcd-library
 * */

/**
 * |----------------------------------------------------------------------
 * | Copyright (c) 2016 Tilen Majerle
 * |
 * | Permission is hereby granted, free of charge, to any person
 * | obtaining a copy of this software and associated documentation
 * | files (the "Software"), to deal in the Software without restriction,
 * | including without limitation the rights to use, copy, modify, merge,
 * | publish, distribute, sublicense, and/or sell copies of the Software,
 * | and to permit persons to whom the Software is furnished to do so,
 * | subject to the following conditions:
 * |
 * | The above copyright notice and this permission notice shall be
 * | included in all copies or substantial portions of the Software.
 * |
 * | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * | EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * | OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * | AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * | HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * | WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * | FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * | OTHER DEALINGS IN THE SOFTWARE.
 * |----------------------------------------------------------------------
 * |  Modified by Jorge A. Santos for use with hal library in stm32f103 boards
 */
#include "lcd.h"
#include "stm32f4_discovery.h"
#include "timer.h"
#include "string.h"
#include "keypad.h"

/* Private variables */
static uint8_t number_of_characters_counter;
static char    first_line[8]				 = "SMI_NGFL";
static uint8_t size_of_first_line_string;

void initLcd(void)
{
	number_of_characters_counter = 0;
	size_of_first_line_string = strlen(first_line);
	//clear
	writeCommand(CMD_LCD_CLEAR);

	//function set : 2 lines, 8 bits and 5x8 dots
	writeCommand(CMD_LCD_FUNCTION_2_LINES_8_BITS);

	//Display on
	writeCommand(CMD_LCD_DISPLAY_ON);


	writeSymbol(first_line, size_of_first_line_string);
	writeCommand(CMD_LCD_CHANGE_LINE);
}

void writeCommand( unsigned short p_command)
{
	GPIO_SetBits(GPIOA, p_command & 0x00FF);
	p_command = p_command >> 8;
	GPIO_SetBits(GPIOB, p_command & 0x0006);

	int delay = 1000000;
	while(delay--){};

	GPIO_SetBits(GPIOB, 0x0001);

	delay = 1000000;
	while(delay--){};

	GPIO_ResetBits(GPIOB, 0x0001);

	delay = 1000000;
	while(delay--){};

	GPIO_ResetBits(GPIOB, 0x0006);
	GPIO_ResetBits(GPIOA, 0x00FF);
}

void writeSymbol(char * p_symbol, uint8_t size_of_symbol)
{
	for (int i = 0; i < size_of_symbol; ++i)
	{
		unsigned short cmd = 0b10000000000 | p_symbol[i];
		writeCommand(cmd);
	}
}

void updateLcd(void)
{
	KEYPAD_BUTTON_type* keypressed_ptr = keypad_update();

	if (keypressed_ptr != (void*)0xFF)
	{
		//do
		//{
		uint8_t key_pressed = keypressed_ptr->keypad_button_value;
		char symbol[1] = {get_symbol(key_pressed)};
		if (symbol[0] == 'A')
		{
			writeCommand(CMD_LCD_CLEAR);
			writeSymbol(first_line, size_of_first_line_string);
			writeCommand(CMD_LCD_CHANGE_LINE);
			number_of_characters_counter = 0;
		}
		else if (number_of_characters_counter < 16)
		{
			writeSymbol(symbol, 1);
			++number_of_characters_counter;
		}
			//	++keypressed_ptr;
		//} while (keypressed_ptr < get_keypad_button(NUMBER_OF_KEYPAD_BUTTON));
}

}
