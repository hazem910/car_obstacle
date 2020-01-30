/*
 * swICU.c
 *
 * Created: 1/29/2020 3:38:40 PM
 *  Author: hazem
 */ 

#include "SwICU.h"
#include "timers.h"
#include "gpio.h"
#include "softwareDelay.h"

volatile uint8_t volatile gvu8_OVFs=0;
volatile uint8_t volatile gvu8_uSeconds=0;

void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge){
	timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_1024, 0, 0, T0_INTERRUPT_NORMAL);
	gpioPinDirection(GPIOA, BIT3, OUTPUT);
	gpioPinDirection(GPIOB,BIT2,INPUT);
	gpioPinWrite(GPIOB,BIT2,HIGH);
	switch (a_en_inputCaptureEdge) {
		case (SwICU_EdgeFalling):
		MCUCSR &= ~(1 << 6);
		break;
		case (SwICU_EdgeRisiging):
		MCUCSR |= (1 << 6);
		break;
		default:
		MCUCSR |= (1 << 6);
		break;
	}
	SwICU_Enable();
}

EN_SwICU_Edge_t SwICU_GetCfgEdge(void){
	if(MCUCSR & (1 << 6))
	return SwICU_EdgeRisiging;
	else
	return SwICU_EdgeFalling;
}

void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdge){
	switch (a_en_inputCaptureEdge) {
		case (SwICU_EdgeFalling):
		MCUCSR &= ~(1 << 6);
		break;
		case (SwICU_EdgeRisiging):
		MCUCSR |= (1 << 6);
		break;
		default:
		MCUCSR |= (1 << 6);
		break;
	}
}

void SwICU_Read(volatile uint8_t* capt){
gpioPinWrite(GPIOA,BIT3,HIGH);
	softwareDelayUS(10);
gpioPinWrite(GPIOA,BIT3,LOW);
softwareDelayUS(500);
	*capt = gvu8_uSeconds;
}

void SwICU_Stop(void){
	TCCR0 = T0_NO_CLOCK; // stop timer0
}

void SwICU_Start(void){
	TCCR0 |= T0_PRESCALER_1024; // start timer0
}

void SwICU_Enable(void){
	GICR |= (1 << 5); // enable INT2
}

void SwICU_Disable(void){
	GICR &= ~(1 << 5); // disable INT2
}

ISR(INT2_vect){
	
	if(SwICU_GetCfgEdge() == SwICU_EdgeRisiging){
		
		gvu8_OVFs=0;
		SwICU_Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
		
	}
	else{
		SwICU_Stop();
		gvu8_uSeconds = TCNT0;
		TCNT0 = 0;
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
		
	
	}
}
ISR(TIMER0_OVF_vect){
gvu8_OVFs++;}