/*
 * timers.c
 *
 * Created: 1/21/2020 11:06:14 AM
 *  Author: hazem
 */ 
#include "timers.h"
static uint8_t global_prescaller=0;
#define  cr_to_delay  (250)
#define  to_prescaller_clear_mask (0xF8)
#define t0_oc_flag 1
#define  cr_to_delay_us (20)
#define  t2_oc_flag (7)
uint16_t initialValue;
uint16_t ocr;

static En_timer1perscaler_t gen_T1_prescale = T1_NO_CLOCK;
static En_timer1Mode_t gen_T1_mode;

typedef enum En_timer1Freq_t{
	FREQ_16_M = 16000000,
	FREQ_2_M = 2000000,
	FREQ_250_K = 250000,
	FREQ_62_5_K = 62500,
	FREQ_15_625_K = 15625
}En_timer1Freq_t;

static En_timer1Freq_t gen_T1_Freq;
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask){
	switch (en_mode)
	{
		case T0_COMP_MODE:
		                  TCCR0|=T0_COMP_MODE;
						  OCR0=u8_outputCompare;
						  break;
		case T0_NORMAL_MODE:
		                   TCCR0|=T0_NORMAL_MODE;
						   break;
	}
	switch(en_OC0){
		case T0_OC0_CLEAR:
		                  TCCR0|=T0_OC0_CLEAR;
						  break;
		case T0_OC0_DIS:
		                TCCR0|=T0_OC0_DIS;
						break;
		case  T0_OC0_SET:
		                TCCR0|=T0_OC0_SET;
						break;			
		case T0_OC0_TOGGLE:
		                  TCCR0|=T0_OC0_TOGGLE;
						  break;
	}
	switch(en_prescal){
	case T0_NO_CLOCK:
	                 global_prescaller=T0_NO_CLOCK;
					 break;
	case  T0_PRESCALER_NO:
	                    global_prescaller=T0_PRESCALER_NO;
						break;
	case T0_PRESCALER_8:
	                    global_prescaller=T0_PRESCALER_8;
	                    break;
	case  T0_PRESCALER_64:					
						global_prescaller=T0_PRESCALER_64;
						break;
	case T0_PRESCALER_256:
	                     global_prescaller=T0_PRESCALER_256;
	                     break;
	case  T0_PRESCALER_1024:
						global_prescaller=T0_PRESCALER_1024;
						break;
						
	}
TCNT0=u8_initialValue;
switch(en_interruptMask){
	case  T0_INTERRUPT_NORMAL:
	                          TIMSK|=T0_INTERRUPT_NORMAL;
							  break;
	case T0_POLLING:
	                     TIMSK=0X00;
					      break;
	case T0_INTERRUPT_CMP:
	                     TIMSK|=T0_INTERRUPT_CMP;
						 break;	
}


}


void timer0Set(uint8_t u8_value){
	
		TCNT0=u8_value;
	
}



uint8_t timer0Read(void){
	
	
	return TCNT0;	
	
}


void timer0Start(void){
	TCCR0|=global_prescaller;

}


void timer0Stop(void){
	TCCR0=0x00;
}


void timer0DelayMs(uint32_t u32_delay_in_ms){
uint32_t au32_loop_counter=0;
OCR0=cr_to_delay;
TCCR0&=to_prescaller_clear_mask;
TCCR0|=T0_PRESCALER_64;
while(au32_loop_counter<=u32_delay_in_ms)
{
	if(GET_BIT(TIFR,t0_oc_flag)){
		
		
		SET_BIT(TIFR,t0_oc_flag);
		au32_loop_counter++;
	}
	
}
TCCR0&=to_prescaller_clear_mask;
}



void timer0DelayUs(uint32_t u32_delay_in_us){
	
uint32_t au32_loop_counter=0;
OCR0=cr_to_delay_us;
TCCR0&=to_prescaller_clear_mask;
TCCR0|=T0_PRESCALER_NO;
while(au32_loop_counter<=u32_delay_in_us)
{
	if(GET_BIT(TIFR,t0_oc_flag)){
		
		
		SET_BIT(TIFR,t0_oc_flag);
		au32_loop_counter++;
	}
	
}
TCCR0&=to_prescaller_clear_mask;
}

/*timer 2*/
void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask){
	
	switch (en_mode)
	{
		case T2_COMP_MODE:
		TCCR2|=T2_COMP_MODE;
		OCR2=u8_outputCompare;
		break;
		case T2_NORMAL_MODE:
		TCCR2|=T2_NORMAL_MODE;
		break;
	}
	switch(en_OC){
		case T2_OC2_CLEAR:
		TCCR2|=T2_OC2_CLEAR;
		break;
		case T2_OC2_DIS:
		TCCR2|=T2_OC2_DIS;
		break;
		case  T2_OC2_SET:
		TCCR2|=T2_OC2_SET;
		break;
		case T2_OC2_TOGGLE:
		TCCR2|=T2_OC2_TOGGLE;
		break;
	}
	switch(en_prescal){
		case T2_NO_CLOCK:
		global_prescaller=T2_NO_CLOCK;
		break;
		case  T2_PRESCALER_NO:
		global_prescaller=T2_PRESCALER_NO;
		break;
		case T2_PRESCALER_8:
		global_prescaller=T2_PRESCALER_8;
		break;
		case T2_PRESCALER_32:
		                    global_prescaller=T2_PRESCALER_32;
		                    break;
		case  T2_PRESCALER_64:
		global_prescaller=T2_PRESCALER_64;
		break;
		case T2_PRESCALER_128:
		 global_prescaller=T2_PRESCALER_128;
		 break;
		case T2_PRESCALER_256:
		global_prescaller=T2_PRESCALER_256;
		break;
		case  T2_PRESCALER_1024:
		global_prescaller=T2_PRESCALER_1024;
		break;
		
	}
	TCNT2=u8_initialValue;
	switch(en_interruptMask){
		case  T2_INTERRUPT_NORMAL:
		TIMSK|=T2_INTERRUPT_NORMAL;
		break;
		case T2_POLLING:
		TIMSK=0X00;
		break;
		case T2_INTERRUPT_CMP:
		TIMSK|=T2_INTERRUPT_CMP;
		break;
	}	
}

void timer2Set(uint8_t u8_a_value){
	TCNT2=u8_a_value;
}

uint8_t timer2Read(void){
	
	
	return TCNT2;
}


void timer2Start(void){
	
		TCCR0|=global_prescaller;

	
}



void timer2Stop(void){
	
	
	TCCR2=0X00;
}



void timer2DelayMs(uint32_t u32_delay_in_ms)
{
	uint32_t au32_loop_counter=0;
	OCR2=cr_to_delay_us;
	TCCR2&=to_prescaller_clear_mask;
	TCCR2|=T2_PRESCALER_64;
	while(au32_loop_counter<=u32_delay_in_ms)
	{
		if(GET_BIT(TIFR,t2_oc_flag)){
			
			
			SET_BIT(TIFR,t2_oc_flag);
			au32_loop_counter++;
		}
		
	}
	TCCR2&=0X00;	
}


void timer2DelayUs(uint32_t u16_delay_in_us){
	
	uint16_t au16_loop_counter=0;
	OCR2=cr_to_delay_us;
	TCCR2&=to_prescaller_clear_mask;
	TCCR2|=T2_PRESCALER_NO;
	while(au16_loop_counter<=u16_delay_in_us)
	{
		if(GET_BIT(TIFR,t0_oc_flag)){
			
			
			SET_BIT(TIFR,t0_oc_flag);
			au16_loop_counter++;
		}
		
	}
	TCCR2&=to_prescaller_clear_mask;
}


/*TIMER 1*/


void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask){
	gen_T1_mode = en_mode;
	TCCR1 |= (en_mode | en_OC);
	gen_T1_prescale = en_prescal;
	TCNT1 = u16_initialValue;
	switch (gen_T1_prescale) {
		case (T1_PRESCALER_NO):
		gen_T1_Freq = FREQ_16_M;
		break;
		case (T1_PRESCALER_8):
		gen_T1_Freq = FREQ_2_M;
		break;
		case (T1_PRESCALER_64):
		gen_T1_Freq = FREQ_250_K;
		break;
		case (T1_PRESCALER_256):
		gen_T1_Freq = FREQ_62_5_K;
		break;
		case (T1_PRESCALER_1024):
		gen_T1_Freq = FREQ_15_625_K;
		break;
		default:
		break;
	}
	OCR1A = u16_outputCompareA;
	OCR1B = u16_outputCompareB;
	ICR1 = u16_inputCapture;
	TIMSK |= en_interruptMask;
}

void timer1Set(uint16_t u16_value){
	
	TCNT1 = u16_value;
}


uint16_t timer1Read(void){
	
return TCNT1;
}


void timer1Start(void){
	TCCR1B |= gen_T1_prescale;
}

void timer1Stop(void){
	TCCR1B &= ~((1 << 2) | (1 << 1) | (1 << 0));
}



void timer1DelayMs(uint16_t u16_delay_in_ms){
	uint16_t i;
	switch(gen_T1_mode){
		case (T1_NORMAL_MODE):
		timer1Start();
		for(i=0;i<u16_delay_in_ms;i++){
			timer1Set(65286); 
			while(!(TIFR & (1 << 2)));
			TIFR |= (1 << 2);
		}
		timer1Stop();
		break;
		case (T1_COMP_MODE_OCR1A_TOP):
		OCR1A = 249;
		timer1Start();
		for(i=0;i<u16_delay_in_ms;i++){
			while(!(TIFR & (1 << 4)));
			TIFR |= (1 << 4);
		}
		timer1Stop();
		break;
		case (T1_COMP_MODE_ICR1_TOP):
		ICR1 = 249;
		timer1Start();
		for(i=0;i<u16_delay_in_ms;i++){
			while(!(TIFR & (1 << 5)));
			TIFR |= (1 << 5);
		}
		timer1Stop();
		break;
		default:
		break;
	}
	
	
	
}


void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	
	
	uint16_t f = u8_frequency * 100;
	uint16_t tcntMax = (gen_T1_Freq / f);
	initialValue = 65535 - tcntMax;

	/* Calculating Duty */
	ocr = (uint16_t)(tcntMax * ((float)u8_dutyCycle/100.0));
	ocr += initialValue;
}