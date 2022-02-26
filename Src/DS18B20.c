#include "DS18B20.h"
#include "LED.h"
#include "stm32f0xx_it.h"

extern TIM_HandleTypeDef htim2;

uint16_t TEMP; // Переменная для хранения значения температуры в 16-ричном виде
uint8_t Temp_byte1, Temp_byte2; // Переменные для хранения данных в первом и втором байте
int Temperature = 0; // переменная для хранения значения температуры в 10-чном виде

//------------------------------------Функция задержки в мкс--------------------------------------------------

void delay_us(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2)<time);
}

//------------------------------------Функция установки пина на выход--------------------------------------------------

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = GPIO_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

//------------------------------------Функция установки пина на вход--------------------------------------------------

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = GPIO_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

//------------------------------------Функция инициализации датчика температуры--------------------------------------------------

uint8_t DS18B20_Start(void)
{
	uint8_t Response = 0; // переменная для хранения импульсов, поступающих с датчика
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // установка пина на выход
	HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);  // подтяжка пина к земле
	delay_us(480);   // задержка сигнала в соответствии с даташитом

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);    // установка пина на вход
	delay_us(80);    // задержка сигнала в соответствии с даташитом

	if (!(HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN))) Response = 1; // Если пин в низком состоянии, то на выходе датчика присутствует импульс
	else Response = -1; // в противном случае импульс отсутствует

	delay_us(400); // Полная задержка сигнала в соответствии с даташитом

	return Response;
}

//------------------------------------Функция записи данных в датчик температуры--------------------------------------------------

void DS18B20_Write(uint8_t data)
{
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // установка пина на выход

	//---------------------Цикл записи данных в 8-битное слово------------------------------
	for (int i = 0; i < 8; i++)
	{
		if ((data & (1 << i)) != 0)  // Если бит установлен в 1
		{
			// Записываем 1

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // установка пина на выход
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, 0);  // подтяжка пина к земле
			delay_us(1);  // задержка сигнала в соответствии с даташитом

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // устновка пина на вход
			delay_us(60);  //задержка сигнала в соответствии с даташитом
		}

		else  // Если бит установлен в 0
		{
			// Записываем 0

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
			delay_us(60);

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
		}
	}
}

//------------------------------------Функция чтения данных с датчика температуры--------------------------------------------------

uint8_t DS18B20_Read(void)
{
	uint8_t value = 0; // переменная для хранения прочитанных данных
	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);

	//---------------------Цикл чтения 8-битного слова------------------------------
	for (int i = 0;i < 8;i++)
	{
		Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);

		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);
		delay_us(2);

		Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
		if (HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN))  // Если пин установлен в 1
		{
			value |= 1 << i;  // прочитываем 1 бит
		}
		delay_us(60);
	}
	return value;
}

//------------------------------ Функция непосредственного получения данных с датчика температуры-----------------------------------

void Get_data_temp(void)
{
	DS18B20_Start();
	DS18B20_Write(0xCC);  // Запись команды "Не использовать 64-битный ROM код"
	DS18B20_Write(0x44);  // Запись команды "Возврат результата состояния датчика"

	DS18B20_Start();
	DS18B20_Write(0xCC);  // Запись команды "Не использовать 64-битный ROM код"
	DS18B20_Write(0xBE);  // Запись команды "Чтение содержимого датчика"

	Temp_byte1 = DS18B20_Read(); // Чтение данных
	Temp_byte2 = DS18B20_Read();
	TEMP = (Temp_byte2<<8)|Temp_byte1; // Запись байтов в переменную
	Temperature = (int)TEMP/16; // Температура в 10-чном формате
}

//--------------------------------Функция отображения температуры------------------------------------------------------

void Indication_temp(void)
{
	Get_data_temp();
	Mode(2); // режим температура
	ledprint_temp(Temperature * 100);
}

