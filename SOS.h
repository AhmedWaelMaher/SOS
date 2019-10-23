/******************************************************************************
 *
 * Module: SmallOperatingSystem
 *
 * File Name: SOS.h
 *
 * Description: Operating system header file
 *
 * Author: Ahmed Wael
 *
 *******************************************************************************/

#ifndef SOS_H_
#define SOS_H_

#include "SOS_config.h"
#include "Timer.h"

typedef void(*ptrToFunction)(void);

#define DELETED 0
#define WAITING   1
#define READY  2

typedef enum{
	FAILED,SUCCEED
}EnmOSError_t;

typedef struct{
	uint8 Timer_ID;
	uint32 System_Tick;
}OS_ConfigType;

typedef struct{
	uint32 periodicity;
	uint16 priority;
	void (*g_function)(void);
	uint8 state;
	uint32 task_counter;
}Task_ConfigType;

extern OS_ConfigType OS_Config;
extern OS_ConfigType *OS_Config_Ptr;
extern Task_ConfigType Task_Config_arr[Tasks_NUM];

extern EnmOSError_t OS_Init (const OS_ConfigType * ConfigPtr);
extern EnmOSError_t OS_DeInit(void);
extern void OS_Run(void);
EnmOSError_t OS_Create_Task(uint32 periodicity,uint16 priority,ptrToFunction FuncName);
EnmOSError_t OS_Delete_Task(ptrToFunction FuncName);
EnmOSError_t OS_Systick_Cal(uint8 tick);
extern void Sleep_Cpu(void);
extern void Wake_Cpu(void);

#endif /* SOS_H_ */
