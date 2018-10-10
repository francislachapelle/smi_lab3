/**
  ******************************************************************************
  * @file    IO_Toggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    15-May-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "gpio.h"
#include "timer.h"
#include "lcd.h"
#include "keypad.h"

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define 	NUMBER_OF_ROWS		2
#define		NUMBER_OF_COLS		16
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	init_gpio();
	init_timer();
	delay_ms(45);
	//TM_LCD_Init(NUMBER_OF_COLS, NUMBER_OF_ROWS);
	unsigned short cmd = 0;

		//clear
		cmd  = 0b01;
		writeCommand(cmd);
	/*
		//home
		cmd  = 0b010;
		writeCommande(cmd);

		//cursor
		cmd  = 0b0111;
		writeCommande(cmd);
	*/
		//set fonction
		cmd  = 0b0110000;
		writeCommand(cmd);

		//Display on
		cmd  = 0b01110;
		writeCommand(cmd);
		/*
		//set fonction
		cmd  = 0b0111111;
		writeCommande(cmd);



		//Entry mode set
		cmd  = 0b0110;
		writeCommand(cmd);

		//W
		writeSymbol('W');
	*/
		/*
		cmd  = 0b0000110011;
		writeCommand(cmd);
		cmd  = 0b01110;
		writeCommand(cmd);
		cmd  = 0b0110;
		writeCommand(cmd);
		cmd  = 0b1001010111;
		writeCommand(cmd);*/
		writeSymbol('SMI_NGFL');
	while (1)
	{
		KEYPAD_BUTTON_type* keypressed_ptr = keypad_update();

		if (keypressed_ptr != (void*)0xFF)
		{
			//do
			//{
			uint8_t key_pressed = keypressed_ptr->keypad_button_value;
			unsigned char symbol = get_symbol(key_pressed);
			if (symbol == 'A')
			{
				cmd  = 0b01;
				writeCommand(cmd);
			}
			else
				writeSymbol(symbol);
			//	++keypressed_ptr;
			//} while (keypressed_ptr < get_keypad_button(NUMBER_OF_KEYPAD_BUTTON));
		}
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
