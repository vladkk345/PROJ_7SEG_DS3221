#include "LED.h"
#include "RTC.h"
#include "DS18B20.h"
uint8_t razr_1 = 0, razr_2 = 0, razr_3 = 0, razr_4 = 0; // Номер индикатора
extern TIME time;

//----------------------------------------------Функция установки и выбора символа-------------------------------------

void segchar (uint8_t seg)
{
	  switch (seg)
      {
		 case 0:
              SA_1;SB_1;SC_1;SD_1;SE_1;SF_1;SG_0;
              break;
         case 1:
              SA_0;SB_1;SC_1;SD_0;SE_0;SF_0;SG_0;
              break;
         case 2:
              SA_1;SB_1;SC_0;SD_1;SE_1;SF_0;SG_1;
              break;
         case 3:
              SA_1;SB_1;SC_1;SD_1;SE_0;SF_0;SG_1;
              break;
         case 4:
              SA_0;SB_1;SC_1;SD_0;SE_0;SF_1;SG_1;
              break;
         case 5:
              SA_1;SB_0;SC_1;SD_1;SE_0;SF_1;SG_1;
              break;
         case 6:
              SA_1;SB_0;SC_1;SD_1;SE_1;SF_1;SG_1;
              break;
         case 7:
              SA_1;SB_1;SC_1;SD_0;SE_0;SF_0;SG_0;
              break;
         case 8:
              SA_1;SB_1;SC_1;SD_1;SE_1;SF_1;SG_1;
              break;
         case 9:
              SA_1;SB_1;SC_1;SD_1;SE_0;SF_1;SG_1;
             break;
         case 10:
        	  SA_1;SB_0;SC_0;SD_1;SE_1;SF_1;SG_0;
        	  break;
         case 11:
              SA_1;SB_1;SC_0;SD_0;SE_0;SF_1;SG_1;
              break;
        }
}

//-----------------------------------------------Функция отображения и вывода данных---------------------------------------

void ledprint(uint16_t number)
{
	  razr_1 = number%10;
      razr_2 = number%100/10;
      razr_3 = number%1000/100;
      razr_4 = number/1000;
}

//-----------------------------------------------Функция отображения и вывода данных температуры---------------------------

void ledprint_temp(uint16_t number)
{
	  razr_1 = 10;
      razr_2 = 11;
      razr_3 = number%1000/100;
      razr_4 = number/1000;
}

//-----------------------------------------------Функция попеременного отображения и вывода трех режимов---------------------------------------

void Print_3_modes()
{
	if (time.sec <= 5)
    {
		Indication_time();
	}

    if (time.sec > 5 && time.sec <= 10)
	{
		Indication_date();
	}

	if (time.sec > 10 && time.sec <= 15)
	{
		Indication_temp();
	}

	if (time.sec > 15 && time.sec <= 20)
	{
		Indication_time();
	}

	if (time.sec > 20 && time.sec <= 25)
	{
		Indication_date();
	}

	if (time.sec > 25 && time.sec <= 30)
	{
		Indication_temp();
	}

	if (time.sec > 30 && time.sec <= 35)
	{
		Indication_time();
	}

	if (time.sec > 35 && time.sec <= 40)
	{
		Indication_date();
	}

	if (time.sec > 40 && time.sec <= 45)
	{
		Indication_temp();
	}

	if (time.sec > 45 && time.sec <= 50)
	{
		Indication_time();
	}

	if (time.sec > 50 && time.sec <= 55)
	{
		Indication_date();
	}

    if (time.sec > 55 && time.sec <= 60)
	{
		Indication_temp();
	}
}

