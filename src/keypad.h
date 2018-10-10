/*
 * keypad.h
 *
 *  Created on: Oct 9, 2018
 *      Author: franc
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "stdint.h"

#define			KEYPAD_PORT				  GPIOA

/* Input */
#define 		KEYPAD_ROW_1_PIN		  GPIO_Pin_0
#define 		KEYPAD_ROW_2_PIN		  GPIO_Pin_1
#define 		KEYPAD_ROW_3_PIN		  GPIO_Pin_2
#define 		KEYPAD_ROW_4_PIN		  GPIO_Pin_3

/* Output */
#define 		KEYPAD_COL_1_PIN		  GPIO_Pin_4
#define 		KEYPAD_COL_2_PIN		  GPIO_Pin_5
#define 		KEYPAD_COL_3_PIN		  GPIO_Pin_6

#define 		KEYPAD_COLUMNS_GPIO		 GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6

#define 		NUMBER_OF_KEYPAD_BUTTON   12

typedef enum
{
	KEY_RELEASED 	     = 0
  , KEY_PRESSED  		 = 1
  , KEY_TRIPLE_TOUCH 	 = 2
} KEY_STATE_t;

typedef struct
{
	uint8_t 		row_gpio;
	uint8_t 		row;
	uint8_t 		column_gpio;
	uint8_t			column;
	KEY_STATE_t		actual_key_state;
	KEY_STATE_t		previous_key_state;
	uint8_t			keypad_button_value;
} KEYPAD_BUTTON_type;

void 				init_keypad(void);
KEYPAD_BUTTON_type* keypad_update(void);
KEYPAD_BUTTON_type* get_keypad_button(uint8_t keypad_button_index);
void scan_columns(void);

#endif /* KEYPAD_H_ */
