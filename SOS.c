/******************************************************************************
 *
 * Module: SmallOperatingSystem
 *
 * File Name: SOS.c
 *
 * Description: Operating system source file
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#include "SOS.h"

/*Task_ConfigType Task_Config_arr[Tasks_NUM];*/

static volatile uint32 g_systick =0;
static volatile uint32 g_indexISR =0;
static volatile uint32 g_creat_counter =0;

void Sleep_Cpu(void){
	MCUCR|=(1<<SE);
}

void Wake_Cpu(void){
	MCUCR&=~(1<<SE);

}

void OS_cal(void){
	PORTA ^= (1<<6);
	for(g_indexISR=0;g_indexISR < g_creat_counter;g_indexISR++){
		Task_Config_arr[g_indexISR].task_counter ++;
	}
}

EnmOSError_t OS_Systick_Cal(uint8 tick){
	EnmOSError_t status = SUCCEED;
	status = Timer_Cal(tick);
	return status;
}

EnmOSError_t OS_Init (const OS_ConfigType * ConfigPtr){
	EnmOSError_t status =SUCCEED;
	g_systick=ConfigPtr->System_Tick;
	switch(ConfigPtr->Timer_ID){
	case TIMER0:
		TIMER_init(TIMER0);
		TIMER0_OVF_setCallBack(OS_cal);
		break;
	case TIMER1:
		TIMER_init(TIMER1);
		TIMER1_OVF_setCallBack(OS_cal);
		break;
	case TIMER2:
		TIMER_init(TIMER2);
		TIMER2_OVF_setCallBack(OS_cal);
		break;
	default:
		status =FAILED;
		break;
	}
	return status;
}

EnmOSError_t OS_DeInit(void){
	EnmOSError_t status =OK;
	status = TIMER_stop(OS_Config_Ptr->Timer_ID);
	return status;
}

EnmOSError_t OS_Create_Task(uint32 periodicity,uint16 priority,ptrToFunction FuncName){
	EnmOSError_t status =SUCCEED;
	Task_ConfigType temp_1;
	Task_ConfigType temp_2;
	uint8 flag = 0;
	uint8 flag_swap =0;
	uint32 index = 0;
	if(g_creat_counter <= Tasks_NUM){
		if(g_creat_counter == 0){
			Task_Config_arr[g_creat_counter].g_function = FuncName;
			Task_Config_arr[g_creat_counter].periodicity = periodicity;
			Task_Config_arr[g_creat_counter].priority = priority;
			Task_Config_arr[g_creat_counter].state = READY;
		}
		else if(priority >= Task_Config_arr[g_creat_counter-1].priority){
			Task_Config_arr[g_creat_counter].g_function = FuncName;
			Task_Config_arr[g_creat_counter].periodicity = periodicity;
			Task_Config_arr[g_creat_counter].priority = priority;
			Task_Config_arr[g_creat_counter].state = READY;
		}
		else{
			for(index=0;index<g_creat_counter;index++){
				if(flag_swap == 0){
					if(priority < Task_Config_arr[index].priority){
						temp_1 = Task_Config_arr[index];
						Task_Config_arr[index].g_function = FuncName;
						Task_Config_arr[index].periodicity = periodicity;
						Task_Config_arr[index].priority = priority;
						Task_Config_arr[index].state = READY;
						flag =1;
						flag_swap = 1;
					}
				}
				if(flag == 1){
					temp_2 = Task_Config_arr[index+1];
					Task_Config_arr[index+1] = temp_1;
					flag=2;
				}
				else if(flag == 2){
					temp_1 = Task_Config_arr[index+1];
					Task_Config_arr[index+1] = temp_2;
					flag=1;
				}
			}
		}
	}
	else {
		status = FAILED;
	}
	g_creat_counter++;

	return status;
}

EnmOSError_t OS_Delete_Task(ptrToFunction FuncName){
	EnmOSError_t status =SUCCEED;
	uint32 index =0;
	uint8 flag_del =0;
	if(g_creat_counter >0){
		for(index = 0;index<g_creat_counter;index++){
			if(Task_Config_arr[index].g_function == FuncName){
				if(index == g_creat_counter-1){
					Task_Config_arr[index].state = DELETED;
					Task_Config_arr[index].g_function = NULL;
					break;
				}
				flag_del =1;
			}
			if(flag_del == 1){
				Task_Config_arr[index] = Task_Config_arr[index+1];
			}
			else{
				status = FAILED;
			}
		}
		g_creat_counter--;
	}
	else{
		status = FAILED;
	}
	return status;
}

void OS_Run(void){
	uint32 l_counter=0;
/*	TIMER_start(TIMER1);*/
	while(1){
/*		PORTA &= ~(1<<7);*/
		for(l_counter =0 ;l_counter < g_creat_counter; l_counter++){
			if((((Task_Config_arr[l_counter].task_counter) == (Task_Config_arr[l_counter].periodicity)) ) \
					&& (((Task_Config_arr[l_counter].periodicity)*2) >= (Task_Config_arr[l_counter].task_counter))){
				Task_Config_arr[l_counter].task_counter=0;
				if(Task_Config_arr[l_counter].state == READY){
					Task_Config_arr[l_counter].g_function();
				}
				else if(Task_Config_arr[l_counter].state == WAITING){
					Task_Config_arr[l_counter].state = READY;
				}
			}
		}
/*		PORTA |= (1<<7);*/
/*		Sleep_Cpu();*/
	}
}
