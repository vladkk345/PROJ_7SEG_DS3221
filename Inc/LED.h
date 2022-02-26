#ifndef LED_H_
#define LED_H_

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "main.h"

//--------------------------------------------------------------------------------
void segchar (uint8_t seg);
void ledprint(uint16_t number);
void ledprint_temp(uint16_t number);
void Print_3_modes(void);
//--------------------------------------------------------------------------------
#define SA 			GPIO_PIN_8 	 // Сегмент A
#define SB 			GPIO_PIN_9   // Сегмент B
#define SC 			GPIO_PIN_10  // Сегмент C
#define SD 			GPIO_PIN_11  // Сегмент D
#define SE			GPIO_PIN_12  // Сегмент E
#define SF 			GPIO_PIN_6   // Сегмент F
#define SG 			GPIO_PIN_7   // Сегмент G
#define SH 			GPIO_PIN_15  // Сегмент H
//--------------------------------------------------------------------------------
#define SA_1 HAL_GPIO_WritePin(GPIOA, SA, GPIO_PIN_SET);  // Установка сегмента А в 1
#define SA_0 HAL_GPIO_WritePin(GPIOA, SA, GPIO_PIN_RESET);// Установка сегмента А в 0
//-----------------------------------
#define SB_1 HAL_GPIO_WritePin(GPIOA, SB, GPIO_PIN_SET);  // Установка сегмента B в 1
#define SB_0 HAL_GPIO_WritePin(GPIOA, SB, GPIO_PIN_RESET);// Установка сегмента B в 0
//---------------------------------
#define SC_1 HAL_GPIO_WritePin(GPIOA, SC, GPIO_PIN_SET);  // Установка сегмента C в 1
#define SC_0 HAL_GPIO_WritePin(GPIOA, SC, GPIO_PIN_RESET);// Установка сегмента C в 0
//----------------------------------
#define SD_1 HAL_GPIO_WritePin(GPIOA, SD, GPIO_PIN_SET);  // Установка сегмента D в 1
#define SD_0 HAL_GPIO_WritePin(GPIOA, SD, GPIO_PIN_RESET);// Установка сегмента D в 0
//------------------------------------
#define SE_1 HAL_GPIO_WritePin(GPIOA, SE, GPIO_PIN_SET);  // Установка сегмента E в 1
#define SE_0 HAL_GPIO_WritePin(GPIOA, SE, GPIO_PIN_RESET);// Установка сегмента E в 0
//-------------------------------------
#define SF_1 HAL_GPIO_WritePin(GPIOC, SF, GPIO_PIN_SET);  // Установка сегмента F в 1
#define SF_0 HAL_GPIO_WritePin(GPIOC, SF, GPIO_PIN_RESET);// Установка сегмента F в 0
//-------------------------------------
#define SG_1 HAL_GPIO_WritePin(GPIOC, SG, GPIO_PIN_SET);  // Установка сегмента G в 1
#define SG_0 HAL_GPIO_WritePin(GPIOC, SG, GPIO_PIN_RESET);// Установка сегмента G в 0
//-------------------------------------
#define SH_1 HAL_GPIO_WritePin(GPIOA, SH, GPIO_PIN_SET);  // Установка сегмента H в 1
#define SH_0 HAL_GPIO_WritePin(GPIOA, SH, GPIO_PIN_RESET);// Установка сегмента H в 0

#endif /* LED_H_ */
