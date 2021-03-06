/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LED.h"
#include "stm32f0xx.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IR_Pin GPIO_PIN_5
#define IR_GPIO_Port GPIOC
#define TEMP_Pin GPIO_PIN_1
#define TEMP_GPIO_Port GPIOB
#define SEG_F_Pin GPIO_PIN_6
#define SEG_F_GPIO_Port GPIOC
#define SEG_G_Pin GPIO_PIN_7
#define SEG_G_GPIO_Port GPIOC
#define SEG_A_Pin GPIO_PIN_8
#define SEG_A_GPIO_Port GPIOA
#define SEG_B_Pin GPIO_PIN_9
#define SEG_B_GPIO_Port GPIOA
#define SEG_C_Pin GPIO_PIN_10
#define SEG_C_GPIO_Port GPIOA
#define SEG_D_Pin GPIO_PIN_11
#define SEG_D_GPIO_Port GPIOA
#define SEG_E_Pin GPIO_PIN_12
#define SEG_E_GPIO_Port GPIOA
#define SEG_H_Pin GPIO_PIN_15
#define SEG_H_GPIO_Port GPIOA
#define RAZR_4_Pin GPIO_PIN_3
#define RAZR_4_GPIO_Port GPIOB
#define RAZR_3_Pin GPIO_PIN_4
#define RAZR_3_GPIO_Port GPIOB
#define RAZR_2_Pin GPIO_PIN_5
#define RAZR_2_GPIO_Port GPIOB
#define RAZR_1_Pin GPIO_PIN_6
#define RAZR_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
typedef struct {
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} TIME;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
