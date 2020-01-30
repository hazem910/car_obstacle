/*
 * main.c
 *
 * Created: 1/30/2020 12:54:26 PM
 *  Author: hazem
 */ 
#define F_CPU 16000000UL
#include "SwICU.h"
#include "led.h"
#include "softwareDelay.h"
#include "HwPWM.h"
#include "dcMotor.h"
uint8_t dist;
uint16_t measure;
extern volatile uint8_t gvu8_OVFs;
uint16_t gu16_counter = 0;

int main (void)
{
	
	
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);

	SwICU_Init(SwICU_EdgeRisiging);
	sei();
	

 
	while(1){
		
		
		SwICU_Read(&dist);
		
		measure = (dist + (gvu8_OVFs * 256));
		gvu8_OVFs = 0;
		measure++;
		MotorDC_Dir(MOT_1, FORWARD);
		MotorDC_Dir(MOT_2, FORWARD);
		MotorDC_Speed_HwPWM(80);
		if(measure<=10){
			MotorDC_Dir(MOT_1, STOP);
			MotorDC_Dir(MOT_2, STOP);
			
		}
		
		

		softwareDelayMs(400);
	}
}
