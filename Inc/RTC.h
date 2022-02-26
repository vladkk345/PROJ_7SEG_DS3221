#ifndef RTC_H_
#define RTC_H_

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "main.h"

//--------------------------------------------------------
uint8_t RTC_ConvertFromDec(int c);
uint8_t RTC_ConvertFromBinDec(uint8_t c);
int RTC_ConvertFromBcd(uint8_t c);
void SetTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void GetTime(void);
void SetTime_hour_tens(uint8_t hour_1);
void SetTime_hour_ones(uint8_t hour_2);
void SetTime_min_tens(uint8_t min_1);
void SetTime_min_ones(uint8_t min_2);
void Indication_time(void);
void Indication_date(void);
//--------------------------------------------------------

#endif /* RTC_H_ */
