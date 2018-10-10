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

void writeSymbol( unsigned char p_symbol)
{
	unsigned short cmd = 0b10000000000 | p_symbol;
	writeCommand(cmd);
}
