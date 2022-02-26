#ifndef DS18B20_H_
#define DS18B20_H_

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "main.h"

// Порт и ножка МК для датчика температуры
#define DS18B20_PORT 					GPIOB
#define DS18B20_PIN 					GPIO_PIN_1

//--------------------------------------------------
void delay_us(uint16_t time);
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t DS18B20_Start(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
void Indication_temp(void);
void Get_data_temp(void);
//--------------------------------------------------

#endif /* DS18B20_H_ */
