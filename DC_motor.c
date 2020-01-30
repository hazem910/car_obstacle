/*
 * DC_motor.c
 *
 * Created: 1/26/2020 2:17:24 PM
 *  Author: hazem
 */ 

#include "gpio.h"
#include "timers.h"
#include "dcMotorConfig.h"
#include "dcMotor.h"
#include "HwPWM.h"


void MotorDC_Init(En_motorType_t en_motor_number){
	HwPWMInit();
	switch (en_motor_number) {
		case (MOT_1):
		gpioPinDirection(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, OUTPUT);
		//gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
		gpioPinDirection(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, OUTPUT);
		break;
		case (MOT_2):
		gpioPinDirection(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, OUTPUT);
		//gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, HIGH);
		gpioPinDirection(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, OUTPUT);
		break;
		default:
		gpioPinDirection(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, OUTPUT);
		gpioPinDirection(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, OUTPUT);
		break;
	}


}


void MotorDC_Dir(En_motorType_t en_motor_number, En_motorDir_t en_motor_dir){
	switch (en_motor_number) {
		case (MOT_1):
		switch (en_motor_dir) {
			case (STOP):
			gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
			break;
			case (FORWARD):
			gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, HIGH);
			gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, LOW);
			break;
			case (BACKWARD):
			gpioPinWrite(MOTOR_OUT_1A_GPIO, MOTOR_OUT_1A_BIT, LOW);
			gpioPinWrite(MOTOR_OUT_1B_GPIO, MOTOR_OUT_1B_BIT, HIGH);
			break;
			default:
			break;
		}
		break;
		case (MOT_2):
		switch (en_motor_dir) {
			case (STOP):
			gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
			gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
			break;
			case (FORWARD):
			gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, HIGH);
			gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, LOW);
			break;
			case (BACKWARD):
			gpioPinWrite(MOTOR_OUT_2A_GPIO, MOTOR_OUT_2A_BIT, LOW);
			gpioPinWrite(MOTOR_OUT_2B_GPIO, MOTOR_OUT_2B_BIT, HIGH);
			break;
			default:
			break;
		}
		break;
		default:
		break;
	}
}

void MotorDC_Speed_PollingWithT0(uint8_t u8_motor_speed){
	
	
	timer1SwPWM(u8_motor_speed, 1);
	
}

void MotorDC_Speed_HwPWM(uint8_t speed){
	HwPWMSetDuty(speed, 1000);
}