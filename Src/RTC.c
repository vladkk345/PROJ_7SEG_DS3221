#include "RTC.h"
#include "stm32f0xx_it.h"
#include "IRremote.h"

extern uint8_t razr_1, razr_2, razr_3, razr_4;
extern I2C_HandleTypeDef hi2c2;
extern unsigned int btn;

TIME time; // переменная типа структуры TIME
extern uint8_t m1, m2, m3, h1, h2, h3; // переменные, хранящие значения времени

//--------------------------------Функция преобразования из 10-чного формама в формат BCD-------------------------------------------

uint8_t RTC_ConvertFromDec(int c)
{
    return (uint8_t)((c/10*16)+ (c%10));
}

//--------------------------------Функция преобразования из формата BCD в 10-чный----------------------------------------------------

int RTC_ConvertFromBcd(uint8_t c)
{
    return (int)( (c/16*10)+ (c%16));
}

//--------------------------Функция установки значения времени и даты (используется при отсутствии возможности корректировки данных с пульта)------------------------------------------

void SetTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	// Запись данных в массив
	set_time[0] = RTC_ConvertFromDec(sec);
	set_time[1] = RTC_ConvertFromDec(min);
	set_time[2] = RTC_ConvertFromDec(hour);
	set_time[3] = RTC_ConvertFromDec(dow);
	set_time[4] = RTC_ConvertFromDec(dom);
	set_time[5] = RTC_ConvertFromDec(month);
	set_time[6] = RTC_ConvertFromDec(year);

	HAL_I2C_Mem_Write(&hi2c2, 0xD0, 0x00,1, set_time,7, 1000); // Запись параметров в шину в соответствии с даташитом на RTC DS3231
}

//--------------------------------Функция получения значения времени и даты ----------------------------------------------------

void GetTime(void)
{
	uint8_t get_time[7];

	HAL_I2C_Mem_Read(&hi2c2, 0xD0, 0x00,1, get_time,7, 1000); // Чтение параметров из шины
	// Преобразование полученных данных
	time.sec = RTC_ConvertFromBcd(get_time[0]);
	time.min = RTC_ConvertFromBcd(get_time[1]);
	time.hour = RTC_ConvertFromBcd(get_time[2]);
	time.dayofweek = RTC_ConvertFromBcd(get_time[3]);
	time.dayofmonth = RTC_ConvertFromBcd(get_time[4]);
	time.month = RTC_ConvertFromBcd(get_time[5]);
	time.year = RTC_ConvertFromBcd(get_time[6]);
}

//-------------------------------Функция установки значения десятков часов------------------------------------------

void SetTime_hour_tens(uint8_t hour_1)
{
	convert_code(hour_1);
	h1 = btn;
	razr_4 = btn%10;
}

//-------------------------------Функция установки значения единиц часов------------------------------------------

void SetTime_hour_ones(uint8_t hour_2)
{
	convert_code(hour_2);
	h2 = btn;
	razr_3 = btn%10;
}

//-------------------------------Функция установки значения десятков минут------------------------------------------

void SetTime_min_tens(uint8_t min_1)
{
	convert_code(min_1);
	m1 = btn;
	razr_2 = btn%10;
}

//-------------------------------Функция установки значения единиц минут------------------------------------------

void SetTime_min_ones(uint8_t min_2)
{
	uint8_t set_time_kor[3];
	convert_code(min_2);
	m2 = btn;
	razr_1 = btn%10;

	// Запись данных в массив
	m3 = (m1 * 10) + m2;
	h3 = (h1 * 10) + h2;
	time.sec = 0;

	// Установка и запись скорректированных параметров (корректировка даты не нарушается, дата установлена заранее)
	set_time_kor[0] = RTC_ConvertFromDec(time.sec);
	set_time_kor[1] = RTC_ConvertFromDec(m3);
	set_time_kor[2] = RTC_ConvertFromDec(h3);
	// Параметры для даты
//	set_time_kor[3] = RTC_ConvertFromDec(2);
//	set_time_kor[4] = RTC_ConvertFromDec(15);
//	set_time_kor[5] = RTC_ConvertFromDec(02);
//	set_time_kor[6] = RTC_ConvertFromDec(22);

	// Запись скорректированных параметров в шину
	HAL_I2C_Mem_Write(&hi2c2, 0xD0, 0x00,1, set_time_kor, 3, 1000);
}

//-------------------------------Функция отображения времени----------------------------------------------------

void Indication_time(void)
{
	Mode(0); // режим время
	ledprint(time.hour*100+time.min);
}

//--------------------------------Функция отображения даты------------------------------------------------------

void Indication_date(void)
{
	Mode(1); // режим дата
	ledprint(time.dayofmonth*100+ time.month);
}
