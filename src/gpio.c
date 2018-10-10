/*
 * gpio.c
 *
 *  Created on: Oct 9, 2018
 *      Author: franc
 */

#include <gpio.h>
#include "stm32f4_discovery.h"

/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

void init_gpio(void)
{


	/* GPIOA Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* GPIOC Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	/* GPIOE Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);



	/* Configure PD1, PD2 and PD4-PD7 in output nopull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Configure PD1, PD2 and PD4-PD7 in output nopull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);


	/* Keypad rows: ROW1 to ROW3 are input. PA0 to PA2 */
	/* Configure PA0, PA1 and PA2 in output nopull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Keypad rows: ROW1 to ROW3 are input. PA0 to PA2 */
	/* Configure PD1, PD2 and PD4-PD7 in output nopull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	GPIO_ResetBits(GPIOD, GPIO_Pin_4);
	GPIO_ResetBits(GPIOD, GPIO_Pin_5);
	GPIO_ResetBits(GPIOD, GPIO_Pin_6);
	GPIO_ResetBits(GPIOD, GPIO_Pin_7);
	GPIO_ResetBits(GPIOE, GPIO_Pin_10);
	GPIO_ResetBits(GPIOE, GPIO_Pin_11);
	GPIO_ResetBits(GPIOE, GPIO_Pin_12);
	GPIO_ResetBits(GPIOE, GPIO_Pin_13);

}
