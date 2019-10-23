/******************************************************************************
 *
 * Module: Applocation
 *
 * File Name: app.c
 *
 * Description: Application layer APIs
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#include "SOS.h"

void LED_1(void){
	PORTA ^= (1<<0);
}

void LED_2(void){
	PORTA ^= (1<<1);
}

void LED_3(void){
	PORTA ^= (1<<2);
	OS_Delete_Task(LED_3);
}

int main(void){
	DDRA =0xff;
	OS_Init(OS_Config_Ptr);
	OS_Create_Task(500, 1, LED_1);
	OS_Create_Task(1000, 2, LED_2);
	OS_Create_Task(200, 2, LED_3);
	SREG |= (1<<7);
	OS_Systick_Cal(1);
	OS_Run();
}
