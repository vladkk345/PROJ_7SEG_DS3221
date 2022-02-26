#ifndef IRREMOTE_H_
#define IRREMOTE_H_

#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "main.h"

extern TIM_HandleTypeDef htim15;

#define RAWBUF 256

// Results returned from the decoder
typedef struct
{
		int decode_type; // NEC
		uint32_t value; // Decoded value [max 32-bits]
		int16_t bits; // Number of bits in decoded value
		volatile uint16_t *rawbuf; // Raw intervals in 50uS ticks
		int16_t rawlen; // Number of records in rawbuf
		int16_t overflow; // True iff IR raw code too long
} decode_results;

//---------------------------------------------------------
typedef struct // The fields are ordered to reduce memory over caused by struct-padding
{
	uint8_t rcvstate; // State Machine state
	uint8_t rawlen; // Counter of entries in rawbuf
	uint16_t timer; // State timer, counts 50uS ticks.
	uint16_t rawbuf[RAWBUF]; // Raw data
	uint8_t overflow; // Raw buffer overflow occurred
} irparams_t;

//---------------------------------------------------------
volatile irparams_t irparams;
decode_results results;

//---------------------------------------------------------
int16_t my_decode(decode_results *results);
uint8_t decodeNEC (decode_results *results);
int MATCH_MARK(int measured_ticks, int desired_us);
int MATCH_SPACE(int measured_ticks, int desired_us);
void my_enableIRIn();
void my_resume();
void convert_code(uint32_t code);

// Port and pin MCU for IR-receive
#define RECIV_PIN (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5))

// Codes of buttons remote control AIWA
#define BTN1			0x76044fe0
#define BTN2			0x76044fd0
#define BTN3			0x76044ff0
#define BTN4			0x76044fc8
#define BTN5			0x76044fe8
#define BTN6			0x76044fd8
#define BTN7			0x76044ff8
#define BTN8			0x76044fc4
#define BTN9			0x76044fe4
#define BTN0			0x76044fd4
#define PWR_RC			0x76044fc0
#define CLK				0x76044fe2
#define REPEAT_RC		0x76044fda
#define SLEEP			0x76044fdc
#define RANDOM			0x76044fea

//---------------------------------------------------------
#define NEC				   1
#define NEC_BITS          32
#define NEC_HDR_MARK    9000
#define NEC_HDR_SPACE   4500
#define NEC_BIT_MARK     560
#define NEC_ONE_SPACE   1690
#define NEC_ZERO_SPACE   560
#define NEC_RPT_SPACE   2250
#define REPEAT 0xFFFFFFFF // Decoded value for NEC when a repeat code is received

//---------------------------------------------------------
#define STATE_IDLE      2
#define STATE_MARK      3
#define STATE_SPACE     4
#define STATE_STOP      5
#define STATE_OVERFLOW  6

// Microseconds per clock interrupt tick
#define USECPERTICK 50

// Upper and Lower percentage tolerances in measurements
#define TOLERANCE 25
#define LTOL (1.0 - (TOLERANCE / 100.))
#define UTOL (1.0 + (TOLERANCE / 100.))

//---------------------------------------------------------
#define GAP_TICKS       100
#define TICKS_LOW(us)   ((int)(((us)*LTOL / USECPERTICK)))
#define TICKS_HIGH(us)  ((int)(((us)*UTOL / USECPERTICK + 1)))

// IR detector output is active low
#define MARK   0
#define SPACE  1
#define MARK_EXCESS 100
#define true 1
#define false 0

#endif /* IRREMOTE_H_ */
