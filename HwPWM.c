/*
 * HwPWM.c
 *
 * Created: 1/30/2020 12:41:43 PM
 *  Author: hazem
 */ 
#include "HwPWM.h"
#include "interrupt.h"

void HwPWMInit(void){
	TCCR1B |= (1 << 4); // Mode 8 of the timer 1
	TCCR1A |= ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
	TCCR1B |= ((1 << 1) | (1 << 0)); // DIV_BY_64
}

void HwPWMSetDuty(uint8_t duty, uint32_t frequency){
	uint16_t freq = (uint16_t)(16000000 / (2 * 64 * frequency));
	ICR1 = freq;
	uint16_t val = (freq * (float)(duty/100.0));
	OCR1A = ICR1 - val;
	OCR1B = OCR1A;
}