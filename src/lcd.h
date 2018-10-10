/**
 * Modified by Francis Lachapelle for SMI.
 * */


/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.net
 * @link    http://stm32f4-discovery.net/2015/07/hal-library-15-hd44780-for-stm32fxxx/
 * @version v1.0
 * @ide     Keil uVision
 * @license MIT
 * @brief   HD44780 LCD driver library for STM32Fxxx
 *
\verbatim
   ----------------------------------------------------------------------
    Copyright (c) 2016 Tilen Majerle

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------
* |  Modified by Jorge A. Santos for use with hal library in stm32f103 boards
\endverbatim
 */
#ifndef TM_LCD_H
#define TM_LCD_H 100

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup TM_STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup TM_HD44780
 * @brief    HD44780 LCD driver library for STM32Fxxx - http://stm32f4-discovery.net/2015/07/hal-library-15-hd44780-for-stm32fxxx/
 * @{
 *
 *	It also supports all HD44780 compatible LCD drivers.
 *
 * \par Default pinout
 *
\verbatim
LCD   STM32Fxxx         DESCRIPTION

GND   GND               Ground
VCC   +5V               Power supply for LCD
V0    Potentiometer	    Contrast voltage. Connect to potentiometer
RS    PB2               Register select, can be overwritten in your project's defines.h file
RW    GND               Read/write
E     PB7               Enable pin, can be overwritten in your project's defines.h file
D0    -                 Data 0 - doesn't care
D1    -                 Data 1 - doesn't care
D2    -                 Data 2 - doesn't care
D3    -                 Data 3 - doesn't  care
D4    PC12              Data 4, can be overwritten in your project's defines.h file
D5    PC13              Data 5, can be overwritten in your project's defines.h file
D6    PB12              Data 6, can be overwritten in your project's defines.h file
D7    PB13              Data 7, can be overwritten in your project's defines.h file
A     +3V3              Back light positive power
K     GND               Ground for back light
\endverbatim
 *
 * If you want to change pinout, do this in your defines.h file with lines below and set your own settings:
 *
\code
//RS - Register select pin
#define LCD_RS_PORT     GPIOB
#define LCD_RS_PIN      GPIO_PIN_2
//E - Enable pin
#define LCD_E_PORT      GPIOB
#define LCD_E_PIN       GPIO_PIN_7
//D4 - Data 4 pin
#define LCD_D4_PORT     GPIOC
#define LCD_D4_PIN      GPIO_PIN_12
//D5 - Data 5 pin
#define LCD_D5_PORT     GPIOC
#define LCD_D5_PIN      GPIO_PIN_13
//D6 - Data 6 pin
#define LCD_D6_PORT     GPIOB
#define LCD_D6_PIN      GPIO_PIN_12
//D7 - Data 7 pin
#define LCD_D7_PORT     GPIOB
#define LCD_D7_PIN      GPIO_PIN_13
\endcode
 *
 * \par Changelog
 *
\verbatim
 Version 1.0
  - First release
\endverbatim
 *
 * \par Dependencies
 *
\verbatim
 - STM32Fxxx HAL
 - defines.h
 - TM DELAY
 - TM GPIO
\endverbatim
 */
#include "stm32f4_discovery.h"
/**
 * @defgroup TM_LCD_Macros
 * @brief    Library defines
 * @{
 */

/* 4 bit mode */
/* Control pins, can be overwritten */
/* RS - Register select pin */
#ifndef LCD_RS_PIN
#define LCD_RS_PORT				GPIOD
#define LCD_RS_PIN				GPIO_Pin_1
#endif
/* E - Enable pin */
#ifndef LCD_E_PIN
#define LCD_E_PORT				GPIOD
#define LCD_E_PIN				GPIO_Pin_2
#endif
/* D0 - Data 0 pin */
#ifndef LCD_D0_PIN
#define LCD_D0_PORT				GPIOE
#define LCD_D0_PIN				GPIO_Pin_10
#endif
/* D1 - Data 1 pin */
#ifndef LCD_D1_PIN
#define LCD_D1_PORT				GPIOE
#define LCD_D1_PIN				GPIO_Pin_11
#endif
/* D2 - Data 2 pin */
#ifndef LCD_D2_PIN
#define LCD_D2_PORT				GPIOE
#define LCD_D2_PIN				GPIO_Pin_12
#endif
/* D3 - Data 3 pin */
#ifndef LCD_D3_PIN
#define LCD_D3_PORT				GPIOE
#define LCD_D3_PIN				GPIO_Pin_13
#endif

/* Data pins */
/* D4 - Data 4 pin */
#ifndef LCD_D4_PIN
#define LCD_D4_PORT				GPIOD
#define LCD_D4_PIN				GPIO_Pin_4
#endif
/* D5 - Data 5 pin */
#ifndef LCD_D5_PIN
#define LCD_D5_PORT				GPIOD
#define LCD_D5_PIN				GPIO_Pin_5
#endif
/* D6 - Data 6 pin */
#ifndef LCD_D6_PIN
#define LCD_D6_PORT				GPIOD
#define LCD_D6_PIN				GPIO_Pin_6
#endif
/* D7 - Data 7 pin */
#ifndef LCD_D7_PIN
#define LCD_D7_PORT				GPIOD
#define LCD_D7_PIN				GPIO_Pin_7
#endif

/**
 * @}
 */

/**
 * @defgroup TM_LCD_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes HD44780 LCD
 * @brief  cols: Width of lcd
 * @param  rows: Height of lcd
 * @retval None
 */
void TM_LCD_Init(uint8_t cols, uint8_t rows);

/**
 * @brief  Turn display on
 * @param  None
 * @retval None
 */
void TM_LCD_DisplayOn(void);

/**
 * @brief  Turn display off
 * @param  None
 * @retval None
 */
void TM_LCD_DisplayOff(void);

/**
 * @brief  Clears entire LCD
 * @param  None
 * @retval None
 */
void TM_LCD_Clear(void);

/**
 * @brief  Puts string on lcd
 * @param  x: X location where string will start
 * @param  y; Y location where string will start
 * @param  *str: pointer to string to display
 * @retval None
 */
void TM_LCD_Puts(uint8_t x, uint8_t y, char* str);

/**
 * @brief  Enables cursor blink
 * @param  None
 * @retval None
 */
void TM_LCD_BlinkOn(void);

/**
 * @brief  Disables cursor blink
 * @param  None
 * @retval None
 */
void TM_LCD_BlinkOff(void);

/**
 * @brief  Shows cursor
 * @param  None
 * @retval None
 */
void TM_LCD_CursorOn(void);

/**
 * @brief  Hides cursor
 * @param  None
 * @retval None
 */
void TM_LCD_CursorOff(void);

/**
 * @brief  Scrolls display to the left
 * @param  None
 * @retval None
 */
void TM_LCD_ScrollLeft(void);

/**
 * @brief  Scrolls display to the right
 * @param  None
 * @retval None
 */
void TM_LCD_ScrollRight(void);

/**
 * @brief  Creates custom character
 * @param  location: Location where to save character on LCD. LCD supports up to 8 custom characters, so locations are 0 - 7
 * @param *data: Pointer to 8-bytes of data for one character
 * @retval None
 */
void TM_LCD_CreateChar(uint8_t location, uint8_t* data);

/**
 * @brief  Puts custom created character on LCD
 * @param  x: X location where character will be shown
 * @param  y: Y location where character will be shown
 * @param  location: Location on LCD where character is stored, 0 - 7
 * @retval None
 */
void TM_LCD_PutCustom(uint8_t x, uint8_t y, uint8_t location);


void update_lcd(void);
void init_lcd(uint8_t cols, uint8_t rows);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
