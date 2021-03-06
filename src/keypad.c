/*
 * keypad.c
 *
 *  Created on: Oct 9, 2018
 *      Author: franc
 */

#include "keypad.h"
#include "stdint.h"
#include "stm32f4_discovery.h"

/* Private variables */
KEYPAD_BUTTON_type	all_keypad_buttons[NUMBER_OF_KEYPAD_BUTTON] = { {.row = 0, .row_gpio = GPIO_Pin_0, .column = 4, .column_gpio = GPIO_Pin_4, .keypad_button_value = 0x01},
																	{.row = 0, .row_gpio = GPIO_Pin_0, .column = 5, .column_gpio = GPIO_Pin_5, .keypad_button_value = 0x02},
																	{.row = 0, .row_gpio = GPIO_Pin_0, .column = 6, .column_gpio = GPIO_Pin_6, .keypad_button_value = 0x03},
																	{.row = 1, .row_gpio = GPIO_Pin_1, .column = 4, .column_gpio = GPIO_Pin_4, .keypad_button_value = 0x04},
																	{.row = 1, .row_gpio = GPIO_Pin_1, .column = 5, .column_gpio = GPIO_Pin_5, .keypad_button_value = 0x05},
																	{.row = 1, .row_gpio = GPIO_Pin_1, .column = 6, .column_gpio = GPIO_Pin_6, .keypad_button_value = 0x06},
																	{.row = 2, .row_gpio = GPIO_Pin_2, .column = 4, .column_gpio = GPIO_Pin_4, .keypad_button_value = 0x07},
																	{.row = 2, .row_gpio = GPIO_Pin_2, .column = 5, .column_gpio = GPIO_Pin_5, .keypad_button_value = 0x08},
																	{.row = 2, .row_gpio = GPIO_Pin_2, .column = 6, .column_gpio = GPIO_Pin_6, .keypad_button_value = 0x09},
																	{.row = 3, .row_gpio = GPIO_Pin_3, .column = 4, .column_gpio = GPIO_Pin_4, .keypad_button_value = 0x0A},
																	{.row = 3, .row_gpio = GPIO_Pin_3, .column = 5, .column_gpio = GPIO_Pin_5, .keypad_button_value = 0x00},
																	{.row = 3, .row_gpio = GPIO_Pin_3, .column = 6, .column_gpio = GPIO_Pin_6, .keypad_button_value = 0x0B} };
KEYPAD_BUTTON_type*	pressed_keypad_buttons[3] 				  = {(KEYPAD_BUTTON_type*)0xFF, (KEYPAD_BUTTON_type*)0xFF, (KEYPAD_BUTTON_type*)0xFF};
KEY_STATE_t		actual_key_state;
KEY_STATE_t		previous_key_state;
uint8_t			keypad_button_value;


uint8_t keypressed_counter;

uint8_t row_gpio_array[4] 	 = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3};

/* Private function prototypes */
void 	read_keys(uint8_t column_index);
void 	set_column(uint8_t column_index);
void 	check_row(uint8_t column_index);

/* Public function definitions */


void init_keypad(void)
{
	keypressed_counter = 0;

	KEYPAD_BUTTON_type* keypad_button_ptr;

	for (keypad_button_ptr = all_keypad_buttons; keypad_button_ptr < &all_keypad_buttons[NUMBER_OF_KEYPAD_BUTTON]; ++keypad_button_ptr)
	{
		keypad_button_ptr->actual_key_state = 	KEY_RELEASED;
		keypad_button_ptr->previous_key_state = KEY_RELEASED;
	}

}

KEYPAD_BUTTON_type* get_keypad_button(uint8_t keypad_button_index)
{
	return &all_keypad_buttons[keypad_button_index];
}

KEYPAD_BUTTON_type* keypad_update(void)
{
	static uint8_t keypad_button_index = 0;

	keypad_button_index = keypad_button_index == NUMBER_OF_KEYPAD_BUTTON ? 0 : keypad_button_index;

	KEYPAD_BUTTON_type* keypad_button_ptr = get_keypad_button(keypad_button_index);

	read_keys(keypad_button_ptr->column);

	switch (keypad_button_ptr->actual_key_state)
	{
		case KEY_RELEASED:
			if(keypad_button_ptr->previous_key_state == KEY_PRESSED)
			{
				keypad_button_ptr->previous_key_state = keypad_button_ptr->actual_key_state;
				keypressed_counter != 0 ? --keypressed_counter : 0;
			}
			++keypad_button_index;
			break;
		case KEY_PRESSED:
			if (keypad_button_ptr->previous_key_state == KEY_RELEASED)
			{
				keypad_button_ptr->previous_key_state = keypad_button_ptr->actual_key_state;
				return keypad_button_ptr;
			}
			break;
		default:
			while(1);
	}
	return (KEYPAD_BUTTON_type*)0xFF;
}

unsigned char get_symbol(uint8_t keypad_button_value)
{
	switch (keypad_button_value)
	{
		case 0x00:
			return '0';
			break;
		case 0x01:
			return '1';
			break;
		case 0x02:
			return '2';
			break;
		case 0x03:
			return '3';
			break;
		case 0x04:
			return '4';
			break;
		case 0x05:
			return '5';
			break;
		case 0x06:
			return '6';
			break;
		case 0x07:
			return '7';
			break;
		case 0x08:
			return '8';
			break;
		case 0x09:
			return '9';
			break;
		case 0x0A:
			return 'A';
			break;
		default:
			while(1);

	}
}

void read_keys(uint8_t column)
{
	for (int column_index = 0; column_index < 3; ++column_index)
	{
		set_column(column_index);
		check_row(column_index);
	}
}

void set_column(uint8_t column_index)
{

	uint8_t actual_column_gpio = get_keypad_button(column_index)->column_gpio;

	GPIO_ResetBits(KEYPAD_PORT, KEYPAD_COLUMNS_GPIO);

	GPIO_SetBits(KEYPAD_PORT, actual_column_gpio);



}

void check_row(uint8_t column_index)
{
	uint8_t keypad_button_index = 0;
	uint8_t row_index = 0;
	do
	{
		keypad_button_index = (3 * row_index + column_index);
		if (GPIO_ReadInputDataBit(KEYPAD_PORT, row_gpio_array[row_index]))
		{
			get_keypad_button(keypad_button_index)->actual_key_state = KEY_PRESSED;
		}
		else
		{
			if (get_keypad_button(keypad_button_index)->previous_key_state == KEY_PRESSED)
			{
				get_keypad_button(keypad_button_index)->actual_key_state = KEY_RELEASED;
			}
		}
		++row_index;
	} while(row_index < 4);
}
