#include "Buttons.h"
#include "IRremote.h"
#include "RTC.h"

uint8_t m1 = 0, m2 = 0, m3 = 0, h1 = 0, h2 = 0, h3 = 0; // Переменные, хранящие значения времени

extern unsigned int btn;
extern uint8_t ind;

//---------------------------------------Функция обработки нажатия кнопок-----------------------------------------------

void Buttons(void)
{
	if (my_decode(&results))
	{
		  btn = (void*)results.value;
		  convert_code(btn);

    //----------------------------------Непосредственная обработка нажатия кнопок по каждому индикатору--------------------------------------------

		  // Проверка допустимых кнопок
		  if ((btn == 0x1 || btn == 0x2 || btn == 0x0) && ind == 1)
		  {
		  	  SetTime_hour_tens(btn); // Запись в первый индикатор
		  }

		  // Проверка недопустимых кнопок
		  else if ((btn == 0x3 || btn == 0x4 || btn == 0x5 || btn == 0x6 || btn == 0x7 || btn == 0x8 || btn == 0x9) && ind == 1)
		  {
		  	  ind--; // Находимся на позиции первого индикатора
		  }

		  if (h1 == 0x2) // Если в первом индикаторе 2
		  {
		     // Проверка допустимых кнопок
		  	 if ((btn == 0x1 || btn == 0x2 || btn == 0x3 || btn == 0x0) && ind == 2)
		  	 {
		  		 SetTime_hour_ones(btn);// Запись во второй индикатор
		  	 }

		  	 // Проверка недопустимых кнопок
		  	 else if ((btn == 0x4 || btn == 0x5 || btn == 0x6 || btn == 0x7 || btn == 0x8 || btn == 0x9) && ind == 2)
		  	 {
		  		 ind--; // Находимся на позиции второго индикатора
		  	 }
		  }

		  else // В противном случае в первом индикаторе 1 или 0
		  {
		  	 // Проверка допустимых кнопок
		  	 if ((btn == 0x1 || btn == 0x2 || btn == 0x3 || btn == 0x4 || btn == 0x5 || btn == 0x6 || btn == 0x7 || btn == 0x8 || btn == 0x9 || btn == 0x0) && ind == 2)
		  	 {
		  		SetTime_hour_ones(btn); // Запись во второй индикатор
		  	 }
		  }

		  // Проверка допустимых кнопок
		  if ((btn == 0x1 || btn == 0x2 || btn == 0x3 || btn == 0x4 || btn == 0x5 || btn == 0x0) && ind == 3)
		  {
		  	 SetTime_min_tens(btn); // Запись во третий индикатор
		  }

		  // Проверка недопустимых кнопок
		  else if ((btn == 0x6 || btn == 0x7 || btn == 0x8 || btn == 0x9) && ind == 3)
		  {
		  	 ind--; // Находимся на позиции третьего индикатора
		  }

		  // Проверка допустимых кнопок
		  if ((btn == 0x1 || btn == 0x2 || btn == 0x3 || btn == 0x4 || btn == 0x5 || btn == 0x6 || btn == 0x7 || btn == 0x8 || btn == 0x9 || btn == 0x0) && ind == 4)
		  {
		  	 SetTime_min_ones(btn); // Запись во четвертый индикатор
		  	 ind = 0; // Обнуление для повторной корректировки времени (без нажатия на кнопку Pon)
		  }
		  ind++; // Увеличиваем индикатор для перехода к следующему

		  my_resume();
	}
}


