/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: Timer_config.c
 *
 * Description: Source file for the Timer link configurations AVR driver
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#include "Timer_config.h"
#include "Timer.h"




/******************TIMERS PARAMETERS***********************/
/*	uint8 OC_ChA_Mode;
	uint8 OC_ChB_Mode;
	uint16 Normal_PreloadedValue;
	uint8 Prescaler;
	uint16 OCR_ChA;
	uint16 OCR_ChB;
	uint8 Interrupt_ChA;
	uint8 Interrupt_ChB;*/

TIMER_SConfg TIMER_cnfg_arr [NUM_OF_TIMERS] =
{
		{TIMER1,OC_DISABLED,OC_DISABLED,0,F_CPU_8,NA,NA,INTERRUPT,INTERRUPT}
};
