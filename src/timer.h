/*
 * timer.h
 *
 *  Created on: Oct 9, 2018
 *      Author: franc
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"

void init_timer(void);
void delay_ms(uint32_t nTime_ms);
void delay_ms_decrement(void);
#endif /* TIMER_H_ */
