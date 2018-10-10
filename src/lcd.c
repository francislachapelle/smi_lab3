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

/* Private HD44780 structure */
typedef struct {
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} LCD_Options_t;

/* Private functions */
static void TM_LCD_Cmd(uint8_t cmd);
static void TM_LCD_Cmd4bit(uint8_t cmd);
static void TM_LCD_Data(uint8_t data);
static void TM_LCD_CursorSet(uint8_t col, uint8_t row);

/* Private variable */
static LCD_Options_t LCD_Opts;

/* Pin definitions */
#define LCD_RS_LOW              GPIO_WriteBit(LCD_RS_PORT, LCD_RS_PIN, Bit_RESET)
#define LCD_RS_HIGH             GPIO_WriteBit(LCD_RS_PORT, LCD_RS_PIN, Bit_SET)
#define LCD_E_LOW               GPIO_WriteBit(LCD_E_PORT, LCD_E_PIN, Bit_RESET)
#define LCD_E_HIGH              GPIO_WriteBit(LCD_E_PORT, LCD_E_PIN, Bit_SET)
#define LCD_Delay(x)            delay_ms(x)
#define LCD_E_BLINK             LCD_E_HIGH; LCD_Delay(1); LCD_E_LOW


/* Commands*/
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define LCD_DISPLAYON           0x04
#define LCD_CURSORON            0x02
#define LCD_BLINKON             0x01

/* Flags for display/cursor shift */
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

/* Flags for function set */
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

void TM_LCD_Init(uint8_t cols, uint8_t rows) {


	/* Set LCD width and height */
	LCD_Opts.Rows = rows;
	LCD_Opts.Cols = cols;

	/* Set cursor pointer to beginning for LCD */
	LCD_Opts.currentX = 0;
	LCD_Opts.currentY = 0;

	LCD_Opts.DisplayFunction = LCD_4BITMODE | LCD_5x8DOTS | LCD_1LINE;
	if (rows > 1) {
		LCD_Opts.DisplayFunction |= LCD_2LINE;
	}

	/* Try to set 4bit mode */
	TM_LCD_Cmd4bit(0x03);
	LCD_Delay(5);

	/* Second try */
	TM_LCD_Cmd4bit(0x03);
	LCD_Delay(5);

	/* Third goo! */
	TM_LCD_Cmd4bit(0x03);
	LCD_Delay(5);

	/* Set 4-bit interface */
	TM_LCD_Cmd4bit(0x02);
	LCD_Delay(2);

	/* Set # lines, font size, etc. */
	TM_LCD_Cmd(LCD_FUNCTIONSET | LCD_Opts.DisplayFunction);

	/* Turn the display on with no cursor or blinking default */
	LCD_Opts.DisplayControl = LCD_DISPLAYON;
	TM_LCD_DisplayOn();

	/* Clear lcd */
	TM_LCD_Clear();

	/* Default font directions */
	LCD_Opts.DisplayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	TM_LCD_Cmd(LCD_ENTRYMODESET | LCD_Opts.DisplayMode);

	/* Delay */
	LCD_Delay(5);
}

void TM_LCD_Clear(void) {
	TM_LCD_Cmd(LCD_CLEARDISPLAY);
	LCD_Delay(1);
}

void TM_LCD_Puts(uint8_t x, uint8_t y, char* str) {
	TM_LCD_CursorSet(x, y);
	while (*str) {
		if (LCD_Opts.currentX >= LCD_Opts.Cols) {
			LCD_Opts.currentX = 0;
			LCD_Opts.currentY++;
			TM_LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		}
		if (*str == '\n') {
			LCD_Opts.currentY++;
			TM_LCD_CursorSet(LCD_Opts.currentX, LCD_Opts.currentY);
		} else if (*str == '\r') {
			TM_LCD_CursorSet(0, LCD_Opts.currentY);
		} else {
			TM_LCD_Data(*str);
			LCD_Opts.currentX++;
		}
		str++;
	}
}

void TM_LCD_DisplayOn(void) {
	LCD_Opts.DisplayControl |= LCD_DISPLAYON;
	TM_LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void TM_LCD_DisplayOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_DISPLAYON;
	TM_LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void TM_LCD_BlinkOn(void) {
	LCD_Opts.DisplayControl |= LCD_BLINKON;
	TM_LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void TM_LCD_BlinkOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_BLINKON;
	TM_LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void TM_LCD_CursorOn(void) {
	LCD_Opts.DisplayControl |= LCD_CURSORON;
	TM_LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void TM_LCD_CursorOff(void) {
	LCD_Opts.DisplayControl &= ~LCD_CURSORON;
	TM_LCD_Cmd(LCD_DISPLAYCONTROL | LCD_Opts.DisplayControl);
}

void TM_LCD_ScrollLeft(void) {
	TM_LCD_Cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void TM_LCD_ScrollRight(void) {
	TM_LCD_Cmd(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void TM_LCD_CreateChar(uint8_t location, uint8_t *data) {
	uint8_t i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	TM_LCD_Cmd(LCD_SETCGRAMADDR | (location << 3));

	for (i = 0; i < 8; i++) {
		TM_LCD_Data(data[i]);
	}
}

void TM_LCD_PutCustom(uint8_t x, uint8_t y, uint8_t location) {
	TM_LCD_CursorSet(x, y);
	TM_LCD_Data(location);
}

/* Private functions */
static void TM_LCD_Cmd(uint8_t cmd) {
	/* Command mode */
	LCD_RS_LOW;

	/* High nibble */
	TM_LCD_Cmd4bit(cmd >> 4);
	/* Low nibble */
	TM_LCD_Cmd4bit(cmd & 0x0F);
}

static void TM_LCD_Data(uint8_t data) {
	/* Data mode */
	LCD_RS_HIGH;

	/* High nibble */
	TM_LCD_Cmd4bit(data >> 4);
	/* Low nibble */
	TM_LCD_Cmd4bit(data & 0x0F);
}

static void TM_LCD_Cmd4bit(uint8_t cmd) {
	/* Set output port */
	GPIO_WriteBit(LCD_D7_PORT, LCD_D7_PIN, (cmd & 0x08));
	GPIO_WriteBit(LCD_D6_PORT, LCD_D6_PIN, (cmd & 0x04));
	GPIO_WriteBit(LCD_D5_PORT, LCD_D5_PIN, (cmd & 0x02));
	GPIO_WriteBit(LCD_D4_PORT, LCD_D4_PIN, (cmd & 0x01));
	LCD_E_BLINK;
}

static void TM_LCD_CursorSet(uint8_t col, uint8_t row) {
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};

	/* Go to beginning */
	if (row >= LCD_Opts.Rows) {
		row = 0;
	}

	/* Set current column and row */
	LCD_Opts.currentX = col;
	LCD_Opts.currentY = row;

	/* Set location address */
	TM_LCD_Cmd(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}


void update_lcd(void)
{
    TM_LCD_CursorOn();
    delay_ms(3000);
    TM_LCD_Puts(0, 0, "STM32");
    delay_ms(3000);
    //Clear LCD
    TM_LCD_Clear();

    //Show cursor
    TM_LCD_CursorOn();

    //Write new text
    TM_LCD_Puts(6, 1, "CLEARED!");
    delay_ms(3000);
}
