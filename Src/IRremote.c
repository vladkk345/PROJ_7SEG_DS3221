#include "IRremote.h"
#include "LED.h"

extern unsigned int btn;
extern uint8_t ind;

//----------------------------------Функция обратного вызова таймера при декодировании сигнала по протоколу NEC------------------------------

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim15)
	{
		uint8_t irdata = RECIV_PIN;

		irparams.timer++;
		if (irparams.rawlen >= RAWBUF) irparams.rcvstate = STATE_OVERFLOW;

		switch (irparams.rcvstate)
		{
			case STATE_IDLE:
				if (irdata == MARK)
				{
					if (irparams.timer < GAP_TICKS)
					{
						irparams.timer = 0;
					}

					else
					{
						irparams.overflow = false;
						irparams.rawlen  = 0;
						irparams.rawbuf[irparams.rawlen++] = irparams.timer;
						irparams.timer = 0;
						irparams.rcvstate = STATE_MARK;
					}
				}
				break;
			case STATE_MARK:
				if (irdata == SPACE)
				{
					irparams.rawbuf[irparams.rawlen++] = irparams.timer;
					irparams.timer = 0;
					irparams.rcvstate = STATE_SPACE;
				}
				break;
			case STATE_SPACE:
				if (irdata == MARK)
				{
					irparams.rawbuf[irparams.rawlen++] = irparams.timer;
					irparams.timer = 0;
					irparams.rcvstate = STATE_MARK;

				}

				else if (irparams.timer > GAP_TICKS)
				{
					irparams.rcvstate = STATE_STOP;
				}
				break;
			case STATE_STOP:
			 	if (irdata == MARK) irparams.timer = 0;
			 	break;
			case STATE_OVERFLOW:
				irparams.overflow = true;
				irparams.rcvstate = STATE_STOP;
				break;
		}
	}
}

//-------------------------------------------Функции, возвращающе количество подсчитанных тактов при декодировании------------------------

int MATCH_MARK(int measured_ticks, int desired_us)
{
	return ((measured_ticks >= TICKS_LOW(desired_us + MARK_EXCESS)) && (measured_ticks <= TICKS_HIGH(desired_us + MARK_EXCESS)));
}

int MATCH_SPACE(int measured_ticks, int desired_us)
{
	return ((measured_ticks >= TICKS_LOW(desired_us - MARK_EXCESS)) && (measured_ticks <= TICKS_HIGH(desired_us - MARK_EXCESS)));
}

//---------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------Функция, определяющая тип протокола принятого сигнала с ИК-пульта------------------------

int16_t my_decode(decode_results *results)
{
	if (irparams.rcvstate != STATE_STOP) return false;

	results->rawbuf = irparams.rawbuf;
	results->rawlen = irparams.rawlen;
	results->overflow = irparams.overflow;

	if (decodeNEC(results)) return true;
	my_enableIRIn();

	return 0;
}

//--------------------------------------------Функция ининициализации таймера для работы с ИК-пультом---------------------------

void my_enableIRIn()
{
	irparams.rcvstate = STATE_IDLE;
	irparams.rawlen = 0;

	__HAL_TIM_SET_COUNTER(&htim15, 0x0000); // Начало отсчета таймера
	HAL_TIM_Base_Start_IT(&htim15);
}

//--------------------------------------------Функция перезапуска ИК-приема для нажатия следующей кнопки---------------------------

void my_resume()
{
	irparams.rcvstate = STATE_IDLE;
	irparams.rawlen = 0;
}

//--------------------------------------------Функция декодирования принятого сигнала по протоколу NEC---------------------------

uint8_t decodeNEC(decode_results *results)
{
	long data = 0;
	int offset = 1;

	if (!MATCH_MARK(results->rawbuf[offset], NEC_HDR_MARK)) return false;
	offset++;

	if ((irparams.rawlen == 4) && MATCH_SPACE(results->rawbuf[offset], NEC_RPT_SPACE) && MATCH_MARK (results->rawbuf[offset + 1], NEC_BIT_MARK ))
	{
		results->bits        = 0;
		results->value       = REPEAT;
		results->decode_type = NEC;
		return true;
	}

	if (irparams.rawlen < (2 * NEC_BITS) + 4)  return false;

	if (!MATCH_SPACE(results->rawbuf[offset], NEC_HDR_SPACE))  return false;
	offset++;


	for (int i = 0;i < NEC_BITS;i++)
	{
		if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK))  return false;
		offset++;

		if (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE))  data = (data << 1) | 1;
		else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE))  data = (data << 1) | 0;
		else return false;
		offset++;
	}

	results->bits = NEC_BITS;
	results->value = data;
	results->decode_type = NEC;

	return true;
}

//------------------------------------------Функция преобразования кода сигнала, полученного с пульта AIWA-----------------------------------------

void convert_code(uint32_t code)
{
	switch (code)
	{
	case (PWR_RC):
		ledprint(0000);
		ind = 0; // Обнуление данных для повторной корректировки времени
		break;
	case (BTN1):
		btn = 0x1;
		break;
	case (BTN2):
		btn = 0x2;
		break;
	case (BTN3):
		btn = 0x3;
		break;
	case (BTN4):
		btn = 0x4;
		break;
	case (BTN5):
		btn = 0x5;
		break;
	case (BTN6):
		btn = 0x6;
		break;
	case (BTN7):
		btn = 0x7;
		break;
	case (BTN8):
		btn = 0x8;
		break;
	case (BTN9):
		btn = 0x9;
		break;
	case (BTN0):
		btn = 0x0;
		break;
	default:
		break;
	}
}
